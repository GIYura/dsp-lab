#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "iir.h"

void IIR_LowPassGenerate(iir_t* filter, double sampleRateHz, double cutoffHz)
{
    assert(filter != NULL);
    assert(sampleRateHz > 0.0);
    assert(cutoffHz > 0.0);
    assert(cutoffHz < sampleRateHz / 2.0);

    filter->b = exp(-2.0 * PI * cutoffHz / sampleRateHz);
    filter->a = 1.0 - filter->b;

    filter->prevOut = 0.0;
}

void IIR_Calculate(iir_t* const filter, const double* const samples, double* output, uint32_t size)
{
    assert(filter != NULL);
    assert(samples != NULL);
    assert(output != NULL);
    assert(size <= RESPONSE_SIZE);

    filter->prevOut = filter->a * samples[0];
    output[0] = filter->prevOut;

    for (uint32_t i = 1; i < size; i++)
    {
        filter->prevOut = filter->a * samples[i] + filter->b * filter->prevOut;
        output[i] = filter->prevOut;

    }
}

void IIR_Print(const iir_t* const filter)
{
    assert(filter != NULL);

    printf("IIR a=%f\n", filter->a);
    printf("IIR b=%f\n", filter->b);
}
