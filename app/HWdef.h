#ifndef HWDEF_H
#define HWDEF_H

#include "hardware/Memory.h"

#define MAX_BUMPERS 10

namespace hardware {

enum Memory_e {
   NOTUSED = 0,
   BUMPER0,
   BUMPER1,
   BUMPER2,
   BUMPER3,
   BUMPER4,
   BUMPER5,
   BUMPER6,
   BUMPER7,
   BUMPER8,
   BUMPER9,
   MEM_SIZE = 128
};

typedef Memory<MEM_SIZE> memory_t;

} // namespace hardware

#endif // HWDEF_H
