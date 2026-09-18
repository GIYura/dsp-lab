#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "interpolation.h"

void Interpolate(const double* const src, uint32_t srcSize, double* const dst, uint32_t dstSize, uint32_t factor)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(factor > 0);
    assert(dstSize == srcSize * factor);

    uint32_t dstIndex = 0;

    memset(dst, 0, sizeof(double) * dstSize);

    for (uint32_t i = 0; i < srcSize; i++)
    {
        dst[dstIndex] = src[i];
        dstIndex += factor;
    }
}
