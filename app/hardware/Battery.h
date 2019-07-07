#ifndef HARDWARE_BATTERY_H
#define HARDWARE_BATTERY_H

namespace hardware {

class Battery
{
public:
   Battery();
   ~Battery() = default;

   int getLevel() const { return _level; }
   void setLevel(int level) { _level = level; }

private:
   int _level;
};

} // namespace hardware

#endif // HARDWARE_BATTERY_H
