#ifndef IIR_H
#define IIR_H

#include <stdint.h>

#include "config.h"

#define RESPONSE_SIZE (1024)

typedef struct
{
    double a;
    double b;
    double prevOut;
} iir_t;

void IIR_LowPassGenerate(iir_t* filter, double sampleRateHz, double cutoffHz);
void IIR_Calculate(iir_t* const filter, const double* const samples, double* output, uint32_t size);
void IIR_Print(const iir_t* const filter);

#endif /* IIR_H */
