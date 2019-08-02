#include "VirtualReality.h"
#include "Ini.h"
#include "Log.h"
#include "OrientationCone.h"
#include "PhysicsDef.h"
#include "XYZrZ.h"

#include <iostream>
#include <string>

VirtualReality::VirtualReality()
   : Drawable{}
   , DoPhysics{}
   , room_{}
   , cylObjs_{}
   , vehicle_{0.15, 0.10, XYZrZ{-1.0, -1.0, 0.0, 35}}
   , ball_{0.15, XYZrZ(1.0, 1.5, 0.15)}
   , chair_(0.5, 0.5, 0.6, XYZrZ(-0.8, -1.5, 0.25, 30))
   , dirt_{}
   , physicsIsRunning_{false}
   , simTaskPhysics_(this, &VirtualReality::process, physics::SIMTIME_MSEC)
{
   SET_FNAME("VirtualReality::VirtualReality()");
   physicsProcesses.push_back(&vehicle_);
   drawables.push_back(&room_);
   drawables.push_back(&vehicle_);
   drawables.push_back(&ball_);
   drawables.push_back(&chair_);
   drawables.push_back(&dirt_);
   LOGI("initialized");
}

VirtualReality::~VirtualReality()
{
   SET_FNAME("VirtualReality::~VirtualReality()");
   simTaskPhysics_.stop();
   vehicle_.stopControlExecute();
   LOGI("");
}

void VirtualReality::draw() const
{
   OrientationCone::OcX.draw();
   OrientationCone::OcY.draw();
   OrientationCone::OcZ.draw();
   std::for_each(drawables.begin(), drawables.end(),
                 std::mem_fun(&Drawable::draw));
}

void VirtualReality::process()
{
   SET_FNAME("VirtualReality::process()");
   XYZrZ currentXYZrZ = vehicle_.getXYZrZ();
   XYZrZ expectedNextXYZrZ = vehicle_.expectedNextXYZrZ();
   math::Circle collisionShape(expectedNextXYZrZ.position, vehicle_.getR());

   Vehicle expectedVehicle(vehicle_.getR(), vehicle_.getH(), expectedNextXYZrZ);
   {
      std::ostringstream msg;
      msg << "Current state vehicle: " << vehicle_.getXYZrZ()
          << " Expected: " << expectedVehicle.getXYZrZ();
      LOGD(msg.str());
   }

   // Reset physicsState
   physicsState[physics::CYLOBJ_COLLISION] = 0;
   physicsState[physics::WALL_COLLISION] = 0;
   vehicleCollisions.clear();
   // Detect collisions
   size_t index = 0;
   bool isCollided = false;
   // collison vehicle with cylinders for expectedNextPosition?

   //    int collisionIterationsMax = 3;
   //    int collisionIteration = 1;

   //    do
   //    {
   //        while(!isCollided && index < cylObjs_{}ize())
   //        {
   //            isCollided =
   //            expectedVehicle.isColliding(cylObjs_{}ndex]); if
   //            (isCollided) physicsState[CYLOBJ_COLLISION] = 1;
   //            ++index;
   //        }
   //        if (expectedVehicle.isColliding(room_))
   //        {
   //            physicsState[WALL_COLLISION] = 1;
   //        }
   //        if (expectedVehicle.isColliding(chair_))
   //        {
   //            physicsState[WALL_COLLISION] = 1;
   //        }
   //        collisionIteration++;

   //    } while (collisionIteration < collisionIterationsMax);

   // calculate delta movement for vehicle (needs just colliding with
   // cyllinders) collison vehicle for walls colsion vehicle for

   // vehicle set currentPosition to currentPostion + delta

   while (!isCollided && index < cylObjs_.size()) {
      isCollided = vehicle_.isColliding(cylObjs_[index]);
      if (isCollided)
         physicsState[physics::CYLOBJ_COLLISION] = 1;
      ++index;
   }
   if (vehicle_.isColliding(room_)) {
      physicsState[physics::WALL_COLLISION] = 1;
   }
   if (vehicle_.isColliding(chair_)) {
      physicsState[physics::WALL_COLLISION] = 1;
   }
   // Check for dirt
   dirt_.removeDirt(vehicle_);
   // Process contained objects
   for (auto &prcs : physicsProcesses) {
      prcs->process();
   }
}

void VirtualReality::init()
{
   SET_FNAME("VirtualReality::init()");
   vehicle_.setXYZrZ(XYZrZ(-1.0, -1.0, 0.0, -35));
   std::vector<std::string> data;
   IniReader().getData(std::string("VR.cylobjects"), data);
   for (const auto &dt : data) {
      std::istringstream is(dt);
      auto *pCylObj = new CylObject(0, 0, XYZrZ(0, 0, 0));
      is >> *pCylObj;
      cylObjs_.push_back(*pCylObj);
      drawables.push_back(pCylObj);
   }
   size_t maxDirtParticles{0};
   IniReader().getData(std::string("VR.maxDirtParticles"), &maxDirtParticles);
   dirt_.generateDirt(room_, maxDirtParticles);
   LOGD("");
}

void VirtualReality::startPhysics()
{
   SET_FNAME("VirtualReality::startPhysics()");
   simTaskPhysics_.start();
   physicsIsRunning_ = true;
   LOGI("++++++ START");
}

void VirtualReality::stopPhysics()
{
   SET_FNAME("VirtualReality::stopPhysics()");
   simTaskPhysics_.stop();
   physicsIsRunning_ = false;
   LOGI(" ------ STOP");
}
