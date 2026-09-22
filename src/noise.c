#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "noise.h"

void NoiseGenerate(double* const noise, uint32_t count, double amplitude)
{
    assert(noise != NULL);
    assert(count > 0);
    assert(amplitude >= 0.0);

    double random;

    for (uint32_t i = 0; i < count; i++)
    {
        random = (double)rand() / (double)RAND_MAX;

        random = 2.0 * random - 1.0;

        noise[i] = amplitude * random;
    }
}

void NoiseAdd(const double* const in, const double* const noise, double* const out, uint32_t count)
{
    assert(in != NULL);
    assert(noise != NULL);
    assert(out != NULL);

    for (uint32_t i = 0; i < count; i++)
    {
        out[i] = in[i] + noise[i];
    }
}
