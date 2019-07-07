#include "VirtualReality.h"
#include "Ini.h"
#include "Log.h"
#include "OrientationCone.h"
#include "PhysicsDef.h"
#include "math/XYZrZ.h"
#include <iostream>
#include <string>

using namespace std;

VirtualReality::VirtualReality()
   : Drawable()
   , DoPhysics()
   , m_room()
   , m_cylObjs()
   , m_vehicle(0.15, 0.10, XYZrZ(-1.0, -1.0, 0.0, 35))
   , m_ball(0.15, XYZrZ(1.0, 1.5, 0.15))
   , m_chair(0.5, 0.5, 0.6, XYZrZ(-0.8, -1.5, 0.25, 30))
   , m_dirt()
   , m_physicsIsRunning(false)
   , m_simTaskPhysics(this, &VirtualReality::process, PHYSICS_SIMTIME_MSEC)
{
   SET_FNAME("VirtualReality::VirtualReality()");
   physicsProcesses.push_back(&m_vehicle);
   drawables.push_back(&m_room);
   drawables.push_back(&m_vehicle);
   drawables.push_back(&m_ball);
   drawables.push_back(&m_chair);
   drawables.push_back(&m_dirt);
   LOGI("initialized");
}

VirtualReality::~VirtualReality()
{
   SET_FNAME("VirtualReality::~VirtualReality()");
   m_simTaskPhysics.stop();
   m_vehicle.stopControlExecute();
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
   XYZrZ currentXYZrZ = m_vehicle.getXYZrZ();
   XYZrZ expectedNextXYZrZ = m_vehicle.expectedNextXYZrZ();
   math::circle_t collisionShape(expectedNextXYZrZ.position,
                                 m_vehicle.getR());

   Vehicle expectedVehicle(m_vehicle.getR(), m_vehicle.getH(),
                           expectedNextXYZrZ);

   std::ostringstream msg;
   msg << "Current state vehicle: " << m_vehicle.getXYZrZ()
       << " Expected: " << expectedVehicle.getXYZrZ();
   LOGD(msg.str());

   // Reset physicsState
   physicsState[CYLOBJ_COLLISION] = 0;
   physicsState[WALL_COLLISION] = 0;
   vehicleCollisions.clear();
   // Detect collisions
   size_t index = 0;
   bool isCollided = false;
   // collison vehicle with cylinders for expectedNextPosition?

   //    int collisionIterationsMax = 3;
   //    int collisionIteration = 1;

   //    do
   //    {
   //        while(!isCollided && index < m_cylObjs.size())
   //        {
   //            isCollided =
   //            expectedVehicle.isColliding(m_cylObjs[index]); if
   //            (isCollided) physicsState[CYLOBJ_COLLISION] = 1;
   //            ++index;
   //        }
   //        if (expectedVehicle.isColliding(m_room))
   //        {
   //            physicsState[WALL_COLLISION] = 1;
   //        }
   //        if (expectedVehicle.isColliding(m_chair))
   //        {
   //            physicsState[WALL_COLLISION] = 1;
   //        }
   //        collisionIteration++;

   //    } while (collisionIteration < collisionIterationsMax);

   // calculate delta movement for vehicle (needs just colliding with
   // cyllinders) collison vehicle for walls colsion vehicle for

   // vehicle set currentPosition to currentPostion + delta

   while (!isCollided && index < m_cylObjs.size()) {
      isCollided = m_vehicle.isColliding(m_cylObjs[index]);
      if (isCollided)
         physicsState[CYLOBJ_COLLISION] = 1;
      ++index;
   }
   if (m_vehicle.isColliding(m_room)) {
      physicsState[WALL_COLLISION] = 1;
   }
   if (m_vehicle.isColliding(m_chair)) {
      physicsState[WALL_COLLISION] = 1;
   }
   // Check for dirt
   m_dirt.removeDirt(m_vehicle);
   // Process contained objects
   std::for_each(physicsProcesses.begin(), physicsProcesses.end(),
                 std::mem_fun(&DoPhysics::process));
}

void VirtualReality::init()
{
   SET_FNAME("VirtualReality::init()");
   m_vehicle.setXYZrZ(XYZrZ(-1.0, -1.0, 0.0, -35));
   vector<string> data;
   IniReader().GetData(string("VR.cylobjects"), data);
   for (size_t i = 0; i < data.size(); ++i) {
      std::istringstream is(data[i]);
      CylObject *pCylObj = new CylObject(0, 0, XYZrZ(0, 0, 0));
      is >> *pCylObj;
      m_cylObjs.push_back(*pCylObj);
      drawables.push_back(pCylObj);
   }
   m_dirt.generateDirt(m_room, 250);
   LOGD("");
}

void VirtualReality::startPhysics()
{
   SET_FNAME("VirtualReality::startPhysics()");
   m_simTaskPhysics.start();
   m_physicsIsRunning = true;
   LOGI("++++++ START");
}

void VirtualReality::stopPhysics()
{
   SET_FNAME("VirtualReality::stopPhysics()");
   m_simTaskPhysics.stop();
   m_physicsIsRunning = false;
   LOGI(" ------ STOP");
}
