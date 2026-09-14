#ifndef SHIFT_H
#define SHIFT_H

#include <stdint.h>

#include "complex.h"

void SignalShift(const double* const in, const complex_t* const shift, complex_t* const out, uint32_t size);

#endif /* SHIFT_H */
