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
   os << rhs.R_ << " " << rhs.H_ << " " << rhs.nextXYZrZ_;
   return os;
}

Vehicle::Vehicle(double R, double H, const XYZrZ &xyzRz)
   : Drawable()
   , DoPhysics()
   , R_(R)
   , H_(H)
   , XYZrZ_(xyzRz)
   , nextXYZrZ_(xyzRz)
   , drawables()
   , collisionDetector()
   , physicsProcesses()
   , IO()
   , IOint(IO)
   , IOext(IO)
   , IRQs()
   , timer(this)
   , memory_()
   , bumper_(*this, -110, 110, 6, memory_, hardware::BUMPER0)
   , motorLeft_(IOext, MOTORLEFT_PWM_INT, MOTORLEFT_FORWARD_BOOL)
   , motorRight_(IOext, MOTORRIGHT_PWM_INT, MOTORRIGHT_FORWARD_BOOL)
   , pBody_(gluNewQuadric())
   , controlExecuteIsRunning_(true)
   , simProgram_(std::thread(&Vehicle::controlExecute, this))
{
   SET_FNAME("Vehicle::Vehicle()");
   // Physics part
   physicsProcesses.push_back(&timer);
   physicsProcesses.push_back(&bumper_);
   physicsProcesses.push_back(&motorLeft_);
   physicsProcesses.push_back(&motorRight_);
   // Drawable part
   gluQuadricDrawStyle(pBody_, GLU_FILL);
   // Control part
   controlInit();
   LOGI("initialized");
}

Vehicle::~Vehicle()
{
   SET_FNAME("Vehicle::~Vehicle()");
   controlExecuteIsRunning_ = false;
   simProgram_.join();
   LOGI("");
}

XYZrZ Vehicle::expectedNextXYZrZ() const
{
   double speedMotorLeft = 1.2;   // 0.6;   //m_motorLeft.getSpeed();
   double speedMotorRight = 1.14; // 0.57; //m_motorRight.getSpeed();
   double translationSpeed = (speedMotorLeft + speedMotorRight) / 2;
   double translation = translationSpeed * physics::SIMTIME_SEC;
   double rotationSpeed = (speedMotorRight - speedMotorLeft) / (2 * R_);
   double rotation = rotationSpeed * physics::SIMTIME_SEC;
   double rz = math::toRadians(XYZrZ_.Rz);

   return {XYZrZ_.position.get_x() + cos(rz) * translation,
           XYZrZ_.position.get_y() + sin(rz) * translation,
           XYZrZ_.position.get_z(), XYZrZ_.Rz + math::toDegrees(rotation)};
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
   double translation = translationSpeed * physics::SIMTIME_SEC;
   double rotationSpeed = (speedMotorRight - speedMotorLeft) / (2 * R_);
   double rotation = rotationSpeed * physics::SIMTIME_SEC;
   double rz = math::toRadians(XYZrZ_.getRz());

   if (physicsState[physics::CYLOBJ_COLLISION] != 1 &&
       physicsState[physics::WALL_COLLISION] != 1) {
      nextXYZrZ_.position.set_x(XYZrZ_.position.get_x() +
                                cos(rz) * translation);
      nextXYZrZ_.position.set_y(XYZrZ_.position.get_y() +
                                sin(rz) * translation);
      nextXYZrZ_.Rz = XYZrZ_.Rz + math::toDegrees(rotation);
   } else {
      static int incr = 0;
      nextXYZrZ_ = XYZrZ_ - math::CartVec(cos(rz) * translation,
                                          sin(rz) * translation, 0);
      // m_nextXYZrZ.position.x = m_XYZrZ.position.x - cos(rz) *
      // translation; m_nextXYZrZ.position.y = m_XYZrZ.position.y - sin(rz)
      // * translation;
      nextXYZrZ_.Rz = XYZrZ_.Rz - 27 + incr;
      ++incr;
      if (incr > 15) {
         incr = 0;
      }
   }
   nextXYZrZ_.Rz = math::normalizeDegrees(nextXYZrZ_.Rz);
   XYZrZ_ = nextXYZrZ_;
}

void Vehicle::draw() const
{
   glPushMatrix();
   XYZrZ_.draw();
   glPointSize(5);
   glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // point color
   glBegin(GL_POINTS);
   glVertex3f(R_ * 0.8, 0.0, H_);
   glEnd();
   glPointSize(1);
   glColor4f(0.5f, 0.5f, 0.5f, 1.0f); // line color
   gluCylinder(pBody_, R_, R_, H_, 20, 20);
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

      while (controlExecuteIsRunning_) {
         ++tick;
         const boost::system_time timeout(
            boost::get_system_time() +
            boost::posix_time::milliseconds(physics::SIMTIME_MSEC * 4));
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
   controlExecuteIsRunning_ = false;
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
   for (size_t wallID = 0; wallID < corners.size(); ++wallID) {
      math::Point closestPoint(room.closestPointWall(wallID, XYZrZ_.position));

      if ((closestPoint - XYZrZ_.position).length() <= R_) {
         double overshoot =
            (R_ - (closestPoint - XYZrZ_.position).length()) / R_;
         ++nCollisions;

         vehicleCollisions.push_back(closestPoint - XYZrZ_.position);

         std::ostringstream msg;
         msg << "WCS: " << closestPoint << " "
             << (closestPoint - XYZrZ_.position) << " " << std::setw(2)
             << int(overshoot * 100) << "%";

         // CartVec delta((closestPoint - m_XYZrZ.position)  * overshoot);
         math::CartVec delta{closestPoint - XYZrZ_.position};
         nextXYZrZ_ = XYZrZ_ + delta;
         msg << " nextXYZrZ: " << nextXYZrZ_;
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
                                  XYZrZ_.position);
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
      for(const auto &collisionPoints : collisionDetector.getCollisionPoints())
      {
         /// In Vehicle CS.
         vehicleCollisions.push_back(collisionPoints - XYZrZ_.position);
      }
      return true;
   }
   return false;
}
