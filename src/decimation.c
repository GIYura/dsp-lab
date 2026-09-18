#include <assert.h>
#include <stddef.h>

#include "decimation.h"

void Decimate(const double* const src, double* const dst, uint32_t size, uint32_t factor)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(factor > 0);

    uint32_t dstSize = 0;

    for (uint32_t i = 0; i < size; i += factor)
    {
        dst[dstSize++] = src[i];
    }
}
