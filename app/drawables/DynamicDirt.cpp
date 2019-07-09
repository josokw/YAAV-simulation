#include "DynamicDirt.h"
#include "Dirt.h"
#include "Log.h"
#include "Room.h"
#include "Vehicle.h"
#include "math/Polygon.h"
#include "math/Random.h"
#include <algorithm>
#include <sstream>
#include <vector>

DynamicDirt::DynamicDirt()
   : Drawable()
{
   _dirt.push_back(Dirt(0.05, XYZrZ(-2.00, 0.30, 0.0)));
   _dirt.push_back(Dirt(0.05, XYZrZ(-1.10, -1.25, 0.0)));
   _dirt.push_back(Dirt(0.04, XYZrZ(-0.10, -1.00, 0.0)));
   _dirt.push_back(Dirt(0.04, XYZrZ(-0.10, 0.25, 0.0)));
   _dirt.push_back(Dirt(0.03, XYZrZ(-0.15, 0.75, 0.0)));
   _initialDirtLevel = _dirt.size();
}

DynamicDirt::DynamicDirt(const std::initializer_list<Dirt> &dirtlist)
   : Drawable()
{
   for (auto i = dirtlist.begin(); i != dirtlist.end(); i++) {
      _dirt.push_back(*i);
   }
   _initialDirtLevel = _dirt.size();
}

void DynamicDirt::draw() const
{
   std::for_each(_dirt.begin(), _dirt.end(),
                 std::mem_fun_ref(&Dirt::draw));
}

void DynamicDirt::generateDirt(const Room &room, size_t maxDirtParticles)
{
   auto corners = room.getCorners();
   _dirt.clear();
   while (_dirt.size() < maxDirtParticles) {
      math::minmaxXYZ_t mm = room.getMinMaxXYZ();
      Dirt dirt = generate(mm.minX + 0.1, mm.maxX - 0.1, mm.minY + 0.1,
                           mm.maxY - 0.1);
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
      XYZrZ dif(vehicle.getXYZrZ() - it->getXYZrZ());
      if (dif.length() < 0.9 * vehicle.getR()) {
         tobeRemoved.push_back(it);
      }
   }
   for (auto it = tobeRemoved.begin(); it < tobeRemoved.end(); ++it) {
      _dirt.erase(*it);
      std::ostringstream msg;
      msg << "#dirt particles: " << _dirt.size() << " dirt level: "
          << (100 * _dirt.size() / double(_initialDirtLevel)) << "%";
      LOGD(msg.str());
   }
}

Dirt DynamicDirt::generate(double minX, double maxX, double minY,
                           double maxY)
{
   double x = getRandom(minX, maxX);
   double y = getRandom(minY, maxY);
   double R = getRandom(0.001, 0.01);

   return Dirt(R, XYZrZ(x, y, 0));
}
