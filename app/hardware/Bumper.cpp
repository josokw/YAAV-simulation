#include "Bumper.h"
#include "HWdef.h"
#include "Log.h"
#include "Memory.h"
#include "Vehicle.h"
#include "math/MathDef.h"
#include "utils/Logger.h"
#include <cmath>
#include <iostream>
#include <sstream>

hardware::Bumper::Bumper(const Vehicle &vehicle, double startAngle,
                         double endAngle, int n, memory_t &memory,
                         size_t index1)
   : hardware::Sensor(memory, index1)
   , DoPhysics()
   , logger_(utils::Logger::instance())
   , vehicle_(vehicle)
   , angles_()
{
   SET_FNAME("Bumper::Bumper()");
   n = std::min(MAX_BUMPERS, n);
   n = std::max(1, n);
   double angleStep = (endAngle - startAngle) / n;
   for (int i = 0; i <= n; ++i) {
      angles_.push_back(startAngle + i * angleStep);
   }
   LOGI("initialized");
}

void hardware::Bumper::process()
{
   SET_FNAME("Bumper::process()");
   // Reset all sensor data to 0
   for (int i = 0; i < MAX_BUMPERS; ++i) {
      _memory.write(byte_t(0), _index1 + i);
   }
   for (size_t i = 0; i < vehicleCollisions.size(); ++i) {
      // phi is in WCS
      double phi =
         // math::toDegrees(std::atan(vehicleCollisions[i].position.get_y() /
         //                           vehicleCollisions[i].position.get_x()));
         math::toDegrees(std::atan(vehicleCollisions[i].get_y() /
                                   vehicleCollisions[i].get_x()));
      // phi in VCS
      phi -= vehicle_.getXYZrZ().Rz;
      phi = math::normalizeDegrees(phi);
      int sensorOffset = calcSensorOffset(phi);
      _memory.write(byte_t(1), _index1 + sensorOffset);
   }
   //  if ((physicsState[CYLOBJ_COLLISION] == 1) ||
   //  (physicsState[WALL_COLLISION] == 1))
   //  {
   //    m_memory.write(byte_t(1), m_index1);
   //  }
   //  else
   //  {
   //    m_memory.write(byte_t(0), m_index1);
   //  }
}

int hardware::Bumper::calcSensorOffset(double collisionAngle) const
{
   SET_FNAME("Bumper::calcSensorOffset()");
   int offset = -1;
   if (collisionAngle > 180) {
      collisionAngle -= 360;
   }
   if (collisionAngle < angles_[0] ||
       collisionAngle > angles_[angles_.size() - 1]) {
      offset = -1;
   } else {
      size_t i = 0;
      while (collisionAngle > angles_[i] && i < angles_.size()) {
         ++i;
      }
      offset = i - 1;
   }
   std::ostringstream msg;
   msg << "collision in VCS: " << int(collisionAngle) << " " << offset;
   LOGD(msg.str());
   return offset;
}
