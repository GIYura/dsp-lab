#ifndef BIQUAD_H
#define BIQUAD_H

#include <stdint.h>

typedef struct
{
    double a[3];
    double b[3];
    double x[2];
    double y[2];
} biquad_t;

void BiquadInit(biquad_t* const biquad);
void BiquadReset(biquad_t* const biquad);
void BiquadSetCoefficients(biquad_t* const biquad, double a1, double a2, double b0, double b1, double b2);
void BiquadProcess(biquad_t* const biquad, const double* const in, double* const out, uint32_t count);
void BiquadStatePrint(const biquad_t* const biquad);
void BiquadCoefficientsPrint(const biquad_t* const biquad);

#endif /* BIQUAD_H */
