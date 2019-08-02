#ifndef VIRTUALREALITY_H
#define VIRTUALREALITY_H

#include "Ball.h"
#include "Block.h"
#include "CylObject.h"
#include "DoPhysics.h"
#include "Drawable.h"
#include "DynamicDirt.h"
#include "PeriodicTask.h"
#include "PhysicsDef.h"
#include "Room.h"
#include "Vehicle.h"

#include <vector>

/// Responsible for all aspects of calculating graphics and physics.
/// Contains a #PeriodicTask for executing physics.
/// The #draw() function must me executed by a thread in the GUI.
class VirtualReality : public Drawable, public physics::DoPhysics
{
public:
   VirtualReality();
   ~VirtualReality() override;
   /// Executes graphics
   void draw() const override;
   /// Excecutes all physics.
   void process() override;
   /// Initializes contained objects.
   void init();
   /// Continues processing physics.
   void startPhysics();
   /// Halts processing physics, stop running.
   void stopPhysics();
   /// Starts stop physics toggle.
   void startStopPhysics() { simTaskPhysics_.startStop(); }
   /// Gets dirt level %
   double getDirtLevel() const { return dirt_.getDirtLevel(); }

private:
   std::vector<Drawable *> drawables;
   std::vector<DoPhysics *> physicsProcesses;
   Room room_;
   std::vector<CylObject> cylObjs_;

public:
   Vehicle vehicle_;

private:
   Ball ball_;
   Block chair_;
   DynamicDirt dirt_;
   std::atomic<bool> physicsIsRunning_;
   PeriodicTask simTaskPhysics_;
};

#endif // VIRTUALREALITY_H
