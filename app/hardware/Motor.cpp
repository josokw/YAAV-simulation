#include "Motor.h"

hardware::Motor::Motor(hardware::IOextern &IOext, int indexPWM,
                       int indexForward)
   : _IOext(IOext)
   , _indexPWM(indexPWM)
   , _indexForward(indexForward)
   , _maxSpeed(0.25)
   , _speed(0)
{
}

void hardware::Motor::process()
{
   if (_IOext.getBOOLout(_indexForward)) {
      _speed = _IOext.getINTout(_indexPWM) * _maxSpeed / 100;
   } else {
      _speed = -_IOext.getINTout(_indexPWM) * _maxSpeed / 100;
   }
}

double hardware::Motor::getSpeed() const
{
   // return m_speed;
   return _maxSpeed;
}
