#include <assert.h>
#include <stddef.h>

#include "shift.h"

void SignalShift(const double* const in, const complex_t* const shift, complex_t* const out, uint32_t size)
{
    assert(in != NULL);
    assert(shift != NULL);
    assert(out != NULL);
    assert(size > 0);

    complex_t value;

    for (uint32_t i = 0; i < size; i++)
    {
        value.real = in[i];
        value.imag = 0.0;
        out[i] = ComplexMul(value, shift[i]);
    }
}
