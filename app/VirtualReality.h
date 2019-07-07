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

/// Reponsible for all aspects of calculating graphics and physics.
/// Contains a #PeriodicTask for executing physics.
/// The #draw() function must me executed by a thread in the GUI.
class VirtualReality : public Drawable, public physics::DoPhysics
{
public:
   VirtualReality();
   virtual ~VirtualReality();
   /// Execute graphics
   virtual void draw() const override;
   /// Excecute all physics.
   virtual void process() override;
   /// Initalize contained objects.
   void init();
   /// Continues processing physics.
   void startPhysics();
   /// Halt processing physics, stop running.
   void stopPhysics();
   /// Start stop physics toggle.
   void startStopPhysics() { m_simTaskPhysics.startStop(); }
   /// Get dirt level %
   double getDirtLevel() const { return m_dirt.getDirtLevel(); }

private:
   std::vector<Drawable *> drawables;
   std::vector<DoPhysics *> physicsProcesses;
   Room m_room;
   std::vector<CylObject> m_cylObjs;

public:
   Vehicle m_vehicle;

private:
   Ball m_ball;
   Block m_chair;
   DynamicDirt m_dirt;
   bool m_physicsIsRunning;
   PeriodicTask m_simTaskPhysics;
};

#endif // VIRTUALREALITY_H
