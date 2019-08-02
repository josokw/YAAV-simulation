#ifndef VEHICLE_H
#define VEHICLE_H

#include "Battery.h"
#include "Bumper.h"
#include "CollisionDetector.h"
#include "Drawable.h"
#include "HWdef.h"
#include "IObus.h"
#include "IOdef.h"
#include "IOextern.h"
#include "IOintern.h"
#include "Memory.h"
#include "Motor.h"
#include "Timer.h"
#include "XYZrZ.h"

#include <atomic>
#include <thread>
#include <vector>

class Block;
class CylObject;
class Room;

/// Represents the autonomous vehicle.
/// \todo Develop hardware components.
class Vehicle : public Drawable, public physics::DoPhysics
{
   friend std::ostream &operator<<(std::ostream &os, const Vehicle &rhs);

public:
   Vehicle(double R, double H, const XYZrZ &xyzRz);
   Vehicle(const Vehicle &) = delete;
   Vehicle &operator=(const Vehicle &) = delete;
   ~Vehicle() override;

   XYZrZ getXYZrZ() const { return XYZrZ_; }
   void setXYZrZ(const XYZrZ &xyzrz) { XYZrZ_ = xyzrz; }
   double getR() const { return R_; }
   double getH() const { return H_; }
   XYZrZ expectedNextXYZrZ() const;

   void draw() const override;
   void process() override;
   /// main program for controlling vehicle
   void controlInit();
   void controlExecute();
   void stopControlExecute();

   math::Circle getCollisionShape() const { return {XYZrZ_.position, R_}; }
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
   double R_;
   double H_;
   XYZrZ XYZrZ_;
   XYZrZ nextXYZrZ_;
   std::vector<Drawable *> drawables;
   physics::CollisionDetector collisionDetector;
   std::vector<DoPhysics *> physicsProcesses;
   hardware::IObus_t IO;
   hardware::IOintern IOint;
   hardware::IOextern IOext;
   hardware::IRQbus<Vehicle, N_IRQ_IN> IRQs;
   hardware::Timer<Vehicle> timer;
   hardware::memory_t memory_;
   hardware::Bumper bumper_;
   hardware::Motor motorLeft_;
   hardware::Motor motorRight_;
   hardware::Battery battery_;
   GLUquadricObj *pBody_;
   volatile std::atomic<bool> controlExecuteIsRunning_;
   std::thread simProgram_;

   void checkIRQs();
};

#endif // VEHICLE_H
