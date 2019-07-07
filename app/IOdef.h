#ifndef IODEF_H
#define IODEF_H

#include "hardware/IObus.h"

// Boolean inputs for processor
enum IOboolIN {
   IRQ0 = 0,
   IRQ1,
   IRQ2,
   IRQ3,
   IRQ4,
   IRQ5,
   IRQ6,
   IRQ7,
   IRQ8,
   IRQ9,
   N_IRQ_IN,
   N_BOOL_IN = N_IRQ_IN
};

// Boolean outputs from processor
enum IOboolOUT {
   MOTORLEFT_FORWARD_BOOL = 0,
   MOTORRIGHT_FORWARD_BOOL,
   N_BOOL_OUT
};

// Integer inputs for processor
enum IOintIN { N_INT_IN = 0 };

// Integer outputs for processor
enum IOintOUT { MOTORLEFT_PWM_INT = 0, MOTORRIGHT_PWM_INT, N_INT_OUT };

namespace hardware {
typedef IObus<N_BOOL_IN, N_BOOL_OUT, N_INT_IN, N_INT_OUT> IObus_t;
}

#endif // IODEF_H
