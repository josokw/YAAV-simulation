#include "DynamicDirt.h"
#include "Dirt.h"
#include "Log.h"
#include "Polygon.h"
#include "Random.h"
#include "Room.h"
#include "Vehicle.h"

#include <algorithm>
#include <sstream>
#include <vector>

DynamicDirt::DynamicDirt()
   : Drawable{}
   , _dirt{}
   , _initialDirtLevel{_dirt.size()}
{
}

void DynamicDirt::draw() const
{
   for (const auto &drt : _dirt) {
      drt.draw();
   }
}

void DynamicDirt::generateDirt(const Room &room, size_t maxDirtParticles)
{
   _dirt.clear();
   while (_dirt.size() < maxDirtParticles) {
      auto mm = room.getMinMaxXYZ();
      Dirt dirt =
         generate(mm.minX + 0.1, mm.maxX - 0.1, mm.minY + 0.1, mm.maxY - 0.1);
      if (room.isInside(dirt.getXYZrZ().position)) {
         _dirt.push_back(dirt);
      }
   }
   _initialDirtLevel = _dirt.size();
}

void DynamicDirt::removeDirt(const Vehicle &vehicle)
{
   SET_FNAME("DynamicDirt::removeDirt()");
   std::vector<std::list<Dirt>::iterator> tobeRemoved;

   for (auto it = _dirt.begin(); it != _dirt.end(); ++it) {
      // XYZrZ dif(vehicle.getXYZrZ() - it->getXYZrZ());
      CartVec dif(vehicle.getXYZrZ().getPosition() -
                  it->getXYZrZ().getPosition());
      if (dif.length() < 0.9 * vehicle.getR()) {
         tobeRemoved.push_back(it);
      }
   }
   for (auto it = tobeRemoved.begin(); it < tobeRemoved.end(); ++it) {
      _dirt.erase(*it);
      std::ostringstream msg;
      msg << "#dirt particles: " << _dirt.size()
          << " dirt level: " << (100 * _dirt.size() / double(_initialDirtLevel))
          << "%";
      LOGD(msg.str());
   }
}

Dirt DynamicDirt::generate(double minX, double maxX, double minY, double maxY)
{
   double x = getRandom(minX, maxX);
   double y = getRandom(minY, maxY);
   double R = getRandom(0.005, 0.01);

   return {R, XYZrZ{x, y, 0.0}};
}
