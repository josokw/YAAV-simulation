#include "Vehicle.h"
#include "Block.h"
#include "CylObject.h"
#include "EventQueue.h"
#include "IObus.h"
#include "Log.h"
#include "MathDef.h"
#include "OrientationCone.h"
#include "Room.h"
#include "XYZrZ.h"

#include <algorithm>
#include <boost/thread/thread.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &os, const Vehicle &rhs)
{
   os << rhs.m_R << " " << rhs.m_H << " " << rhs.m_nextXYZrZ;
   return os;
}

Vehicle::Vehicle(double R, double H, const XYZrZ &xyzRz)
   : Drawable()
   , DoPhysics()
   , m_R(R)
   , m_H(H)
   , m_XYZrZ(xyzRz)
   , m_nextXYZrZ(xyzRz)
   , drawables()
   , collisionDetector()
   , physicsProcesses()
   , IO()
   , IOint(IO)
   , IOext(IO)
   , IRQs()
   , timer(this)
   , memory()
   , m_Bumper(*this, -110, 110, 6, memory, hardware::BUMPER0)
   , m_motorLeft(IOext, MOTORLEFT_PWM_INT, MOTORLEFT_FORWARD_BOOL)
   , m_motorRight(IOext, MOTORRIGHT_PWM_INT, MOTORRIGHT_FORWARD_BOOL)
   , m_pBody(gluNewQuadric())
   , m_controlExecuteIsRunning(true)
   , m_simProgram(std::thread(&Vehicle::controlExecute, this))
{
   SET_FNAME("Vehicle::Vehicle()");
   // Physics part
   physicsProcesses.push_back(&timer);
   physicsProcesses.push_back(&m_Bumper);
   physicsProcesses.push_back(&m_motorLeft);
   physicsProcesses.push_back(&m_motorRight);
   // Drawable part
   gluQuadricDrawStyle(m_pBody, GLU_FILL);
   // Control part
   controlInit();
   LOGI("initialized");
}

Vehicle::~Vehicle()
{
   SET_FNAME("Vehicle::~Vehicle()");
   m_controlExecuteIsRunning = false;
   m_simProgram.join();
   LOGI("");
}

XYZrZ Vehicle::expectedNextXYZrZ() const
{
   double speedMotorLeft = 1.2;   // 0.6;   //m_motorLeft.getSpeed();
   double speedMotorRight = 1.14; // 0.57; //m_motorRight.getSpeed();
   double translationSpeed = (speedMotorLeft + speedMotorRight) / 2;
   double translation = translationSpeed * PHYSICS_SIMTIME_SEC;
   double rotationSpeed = (speedMotorRight - speedMotorLeft) / (2 * m_R);
   double rotation = rotationSpeed * PHYSICS_SIMTIME_SEC;
   double rz = math::toRadians(m_XYZrZ.Rz);

   return {m_XYZrZ.position.get_x() + cos(rz) * translation,
           m_XYZrZ.position.get_y() + sin(rz) * translation,
           m_XYZrZ.position.get_z(), m_XYZrZ.Rz + math::toDegrees(rotation)};
}

/// @todo Remove vehicle control from physics to controlExecute.
void Vehicle::process()
{
   SET_FNAME("Vehicle::process()");
   checkIRQs();
   std::for_each(physicsProcesses.begin(), physicsProcesses.end(),
                 std::mem_fun(&DoPhysics::process));

   // Vehicle physics
   double speedMotorLeft = 1.2;   // 0.6;   //m_motorLeft.getSpeed();
   double speedMotorRight = 1.14; // 0.57; //m_motorRight.getSpeed();
   double translationSpeed = (speedMotorLeft + speedMotorRight) / 2;
   double translation = translationSpeed * PHYSICS_SIMTIME_SEC;
   double rotationSpeed = (speedMotorRight - speedMotorLeft) / (2 * m_R);
   double rotation = rotationSpeed * PHYSICS_SIMTIME_SEC;
   double rz = math::toRadians(m_XYZrZ.getRz());

   if (physicsState[CYLOBJ_COLLISION] != 1 &&
       physicsState[WALL_COLLISION] != 1) {
      m_nextXYZrZ.position.set_x(m_XYZrZ.position.get_x() +
                                 cos(rz) * translation);
      m_nextXYZrZ.position.set_y(m_XYZrZ.position.get_y() +
                                 sin(rz) * translation);
      m_nextXYZrZ.Rz = m_XYZrZ.Rz + math::toDegrees(rotation);
   } else {
      static int incr = 0;
      m_nextXYZrZ =
         m_XYZrZ - CartVec(cos(rz) * translation, sin(rz) * translation, 0);
      // m_nextXYZrZ.position.x = m_XYZrZ.position.x - cos(rz) *
      // translation; m_nextXYZrZ.position.y = m_XYZrZ.position.y - sin(rz)
      // * translation;
      m_nextXYZrZ.Rz = m_XYZrZ.Rz - 27 + incr;
      ++incr;
      if (incr > 15) {
         incr = 0;
      }
   }
   m_nextXYZrZ.Rz = math::normalizeDegrees(m_nextXYZrZ.Rz);
   m_XYZrZ = m_nextXYZrZ;
}

void Vehicle::draw() const
{
   glPushMatrix();
   m_XYZrZ.draw();
   glPointSize(5);
   glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // point color
   glBegin(GL_POINTS);
   glVertex3f(m_R * 0.8, 0.0, m_H);
   glEnd();
   glPointSize(1);
   glColor4f(0.5f, 0.5f, 0.5f, 1.0f); // line color
   gluCylinder(m_pBody, m_R, m_R, m_H, 20, 20);
   glPopMatrix();
   std::for_each(drawables.begin(), drawables.end(),
                 std::mem_fun(&Drawable::draw));
}

void Vehicle::controlInit()
{
   SET_FNAME("Vehicle::controlInit()");
   // Install ISRs
   IRQs[IRQ0].setISR(&Vehicle::ISR0);
   IRQs[IRQ1].setISR(&Vehicle::ISR1);
   IRQs[IRQ2].setISR(&Vehicle::ISR2);
   // Init timers
   timer.setISR(&Vehicle::ISR0);
   timer.setTime(10000L, hardware::mode_t::PERIODIC);
   timer.start();
   // Init shared vars
   shared1 = shared2 = 1;
   LOGI("ready");
}

void Vehicle::controlExecute()
{
   SET_FNAME("Vehicle::controlExecute()");
   LOGI("started");
   try {
      unsigned long long tick = 0ull;
      EventQueue eventQueue;

      while (m_controlExecuteIsRunning) {
         ++tick;
         const boost::system_time timeout(
            boost::get_system_time() +
            boost::posix_time::milliseconds(PHYSICS_SIMTIME_MSEC * 4));
         if (tick % 10 == 0)
            eventQueue.post(1);
         boost::thread::sleep(timeout);
         // std::this_thread::sleep_for(timeout);
      }
   }
   catch (std::exception &x) {
      LOGE(x.what());
   }
   catch (...) {
      LOGE("UNKNOWN EXCEPTION");
   }
   LOGI("stopped");
}

void Vehicle::stopControlExecute()
{
   m_controlExecuteIsRunning = false;
}

void Vehicle::ISR0()
{
   SET_FNAME("Vehicle::ISR0()");
   LOGI("Heartbeat ------------------------->");
}

void Vehicle::ISR1() {}

void Vehicle::ISR2() {}

void Vehicle::checkIRQs()
{
   for (int i = IRQ0; i < N_IRQ_IN; ++i) {
      IRQs[i].react(this);
   }
}

/// \bug Sometimes vehicle remains colliding walls in an endless loop.
bool Vehicle::isColliding(const Room &room)
{
   SET_FNAME("Vehicle::isColliding()");
   if (collisionDetector.isColliding(getCollisionShape(),
                                     room.getCollisionShape())) {
      const size_t maxIteration = 4;
      size_t iteration = 0;
      while (iteration < maxIteration) {
         ++iteration;
      }
   }
   const auto &corners(room.getCorners());
   int nCollisions = 0;
   for (size_t wallID = 0; wallID < corners.size() - 1; ++wallID) {
      Point closestPoint(room.closestPointWall(wallID, m_XYZrZ.position));

      if ((closestPoint - m_XYZrZ.position).length() <= m_R) {
         double overshoot =
            (m_R - (closestPoint - m_XYZrZ.position).length()) / m_R;
         ++nCollisions;

         vehicleCollisions.push_back(closestPoint - m_XYZrZ.position);

         std::ostringstream msg;
         msg << "WCS: " << closestPoint << " "
             << (closestPoint - m_XYZrZ.position) << " " << std::setw(2)
             << int(overshoot * 100) << "%";

         // CartVec delta((closestPoint - m_XYZrZ.position)  * overshoot);
         CartVec delta{closestPoint - m_XYZrZ.position};
         m_nextXYZrZ = m_XYZrZ + delta;
         msg << " nextXYZrZ: " << m_nextXYZrZ;
         LOGD(msg.str());
      }
   }
   return nCollisions > 0;
}

bool Vehicle::isColliding(const CylObject &object)
{
   SET_FNAME("Vehicle::isColliding()");
   vehicleCollisions.clear();
   if (collisionDetector.isColliding(getCollisionShape(),
                                     object.getCollisionShape())) {
      /// In Vehicle CS.
      vehicleCollisions.push_back(collisionDetector.getCollisionPoints()[0] -
                                  m_XYZrZ.position);
      return true;
   }
   return false;
}

bool Vehicle::isColliding(const Block &object)
{
   SET_FNAME("Vehicle::isColliding()");
   vehicleCollisions.clear();
   if (collisionDetector.isColliding(getCollisionShape(),
                                     object.getCollisionShape())) {
      {
         std::ostringstream msg;
         msg << "############# Is colliding with block";
         LOGD(msg.str());
      }
      for (size_t i = 0; i < collisionDetector.getCollisionPoints().size();
           i++) {
         /// In Vehicle CS.
         vehicleCollisions.push_back(collisionDetector.getCollisionPoints()[i] -
                                     m_XYZrZ.position);
      }
      return true;
   }
   return false;
}
