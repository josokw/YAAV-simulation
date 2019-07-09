#ifndef DYNAMICDIRT_H
#define DYNAMICDIRT_H

#include "Dirt.h"
#include "Drawable.h"

#include <initializer_list>
#include <list>

class Room;
class Vehicle;

/// DynamicDirt manages Dirt objects (creating and removing).
/// They can be removed by physics calculations if the vehicle is above the
/// dirt object.
/// @short Creates and removes Dirt objects.
class DynamicDirt : public Drawable
{
public:
   DynamicDirt();
   DynamicDirt(const std::initializer_list<Dirt> &dirtlist);
   ~DynamicDirt() override = default;

   void draw() const override;
   /// Generates randomly #maxDustParticles Dirt objects inside the room.
   /// @pre Room object must contain a valid polygon representing the
   /// corners.
   void generateDirt(const Room &room, size_t maxDirtParticles);
   /// Returns percentage value dirt level.
   double getDirtLevel() const
   {
      return 100 * _dirt.size() / static_cast<double>(_initialDirtLevel);
   }
   /// Removes Dirt object in #_dirt if vehicle is positioned above the
   /// dirt.
   void removeDirt(const Vehicle &vehicle);

private:
   std::list<Dirt> _dirt;
   size_t _initialDirtLevel;
   Dirt generate(double minX, double maxX, double minY, double maxY);
};

#endif // DYNAMICDIRT_H
