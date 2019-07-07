#ifndef HARDWARE_MOTOR_H
#define HARDWARE_MOTOR_H

#include "DoPhysics.h"
#include "IOextern.h"
#include "PhysicsDef.h"

namespace hardware {

class Motor : public physics::DoPhysics
{
public:
   Motor(hardware::IOextern &IOext, int indexPWM, int indexForward);
   virtual ~Motor() override = default;

   virtual void process() override;
   double getSpeed() const;

private:
   hardware::IOextern &_IOext;
   const int _indexPWM;
   const int _indexForward;
   const int _maxSpeed;
   double _speed;
};

} // namespace hardware

#endif // HARDWARE_MOTOR_H
