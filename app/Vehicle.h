#ifndef VEHICLE_H
#define VEHICLE_H

#include "Drawable.h"
#include "HWdef.h"
#include "IOdef.h"
#include "hardware/Battery.h"
#include "hardware/Bumper.h"
#include "hardware/IObus.h"
#include "hardware/IOextern.h"
#include "hardware/IOintern.h"
#include "hardware/Memory.h"
#include "hardware/Motor.h"
#include "hardware/Timer.h"
#include "math/MathDef.h"
#include "math/XYZrZ.h"
#include "physics/CollisionDetector.h"
// #include <boost/thread/thread.hpp>
#include <thread>
#include <vector>

class Block;
class CylObject;
class Room;

class Vehicle : public Drawable, public physics::DoPhysics
{
   friend std::ostream &operator<<(std::ostream &os, const Vehicle &rhs);

public:
   Vehicle(double R, double H, const XYZrZ &xyzRz);
   Vehicle(const Vehicle &) = delete;
   Vehicle &operator=(const Vehicle &) = delete;
   virtual ~Vehicle();

   XYZrZ getXYZrZ() const { return m_XYZrZ; }
   void setXYZrZ(const XYZrZ &xyzrz) { m_XYZrZ = xyzrz; }
   double getR() const { return m_R; }
   double getH() const { return m_H; }
   XYZrZ expectedNextXYZrZ() const;

   virtual void draw() const;
   virtual void process();
   /// main program for controlling vehicle
   void controlInit();
   void controlExecute();
   void stopControlExecute();

   math::circle_t getCollisionShape() const
   {
      return math::circle_t(m_XYZrZ.position, m_R);
   }
   bool isColliding(const Room &room);
   bool isColliding(const CylObject &object);
   bool isColliding(const Block &object);

   void reset();
   void start();
   void stop();

   void ISRnull() {}
   void ISR0();
   void ISR1();
   void ISR2();

   volatile int shared1;
   volatile int shared2;

private:
   double m_R;
   double m_H;
   XYZrZ m_XYZrZ;
   XYZrZ m_nextXYZrZ;
   std::vector<Drawable *> drawables;
   physics::CollisionDetector collisionDetector;
   std::vector<DoPhysics *> physicsProcesses;
   hardware::IObus_t IO;
   hardware::IOintern IOint;
   hardware::IOextern IOext;
   hardware::IRQbus<Vehicle, N_IRQ_IN> IRQs;
   hardware::Timer<Vehicle> timer;
   hardware::memory_t memory;
   hardware::Bumper m_Bumper;
   hardware::Motor m_motorLeft;
   hardware::Motor m_motorRight;
   hardware::Battery m_battery;
   GLUquadricObj *m_pBody;
   volatile bool m_controlExecuteIsRunning;
   std::thread m_simProgram;

   void checkIRQs();
};

#endif // VEHICLE_H
