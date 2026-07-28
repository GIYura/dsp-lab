#include <assert.h>
#include <stddef.h>
#include "convolution.h"

void Convolution(const double* const src, double* const dst, const double* const impulseResponse, uint32_t srcLen, uint32_t impulseResponseLen)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(impulseResponse != NULL);
    assert(srcLen > 0U);
    assert(impulseResponseLen > 0U);

    uint32_t dstLen = srcLen + impulseResponseLen - 1U;

    for (uint32_t i = 0; i < dstLen; i++)
    {
        dst[i] = 0.0;
    }

    for (uint32_t i = 0; i < srcLen; i++)
    {
        for (uint32_t j = 0; j < impulseResponseLen; j++)
        {
            dst[i + j] += src[i] * impulseResponse[j];
        }
    }
}
