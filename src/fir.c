#include <assert.h>
#include <math.h>
#include <stddef.h>

#include "fir.h"
#include "window.h"
#include "config.h"

void FIR_LowPassGenerate(double *coefficients, uint32_t tapCount, double sampleRateHz, double cutoffHz)
{
    assert(coefficients != NULL);
    assert(sampleRateHz > 0.0);
    assert(cutoffHz > 0.0);
    assert(cutoffHz < sampleRateHz / 2.0);
    assert((tapCount & 1U) != 0U);

    double center;
    double m;
    double ideal;

    center = (double)(tapCount - 1) / 2.0;

    for (uint32_t i = 0; i < tapCount; i++)
    {
        m = (double)i - center;
        if (fabs(m) < 1e-12)
        {
            ideal = 2.0 * cutoffHz / sampleRateHz;
        }
        else
        {
            ideal = sin(2.0 * PI * cutoffHz * m / sampleRateHz) / (PI * m);
        }

        coefficients[i] = ideal;
    }
}

void FIR_Normalize(const double* const src, double* const dst, uint32_t size)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(size > 0U);

    double sum = 0.0;

    for (uint32_t i = 0; i < size; i++)
    {
        sum += src[i];
    }

    for (uint32_t i = 0; i < size; i++)
    {
        dst[i] = src[i] / sum;
    }
}
