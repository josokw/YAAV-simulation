#ifndef HARDWARE_BATTERY_H
#define HARDWARE_BATTERY_H

namespace hardware {

class Battery
{
public:
   Battery();
   ~Battery() = default;

   int getLevel() const { return level_; }
   void setLevel(int level) { level_ = level; }

private:
   int level_;
};

} // namespace hardware

#endif // HARDWARE_BATTERY_H
