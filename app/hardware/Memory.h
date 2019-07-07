#ifndef HARDWARE_MEMORY_H
#define HARDWARE_MEMORY_H

#include <array>
#include <cstddef>

namespace hardware {

using byte_t = unsigned char;

template <size_t N> class Memory
{
public:
   Memory()
      : _memory()
   {
   }
   virtual ~Memory() = default;

   void write(byte_t value, size_t offset) { _memory[offset] = value; }
   void write(int value, size_t offset)
   {
      *(static_cast<int *>(&_memory[offset])) = value;
   }
   void write(bool value, size_t offset)
   {
      *(static_cast<bool *>(&_memory[offset])) = value;
   }
   void read(byte_t &value, size_t offset) const
   {
      value = _memory[offset];
   }
   void read(int &value, size_t offset) const
   {
      value = *(static_cast<int *>(&_memory[offset]));
   }
   void read(bool &value, size_t offset) const
   {
      value = *(static_cast<bool *>(&_memory[offset]));
   }

private:
   std::array<byte_t, N> _memory;
};

} // namespace hardware

#endif // HARDWARE_MEMORY_H
