#include <assert.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

#include "biquad.h"

static double ProcessSample(biquad_t* const biquad, double in)
{
    assert(biquad != NULL);

    double y = 0.0;

    y = biquad->b[0] * in + biquad->b[1] * biquad->x[0] + biquad->b[2] * biquad->x[1] - biquad->a[1] * biquad->y[0] - biquad->a[2] * biquad->y[1];

    biquad->x[1] = biquad->x[0];
    biquad->x[0] = in;

    biquad->y[1] = biquad->y[0];
    biquad->y[0] = y;

    return y;
}

void BiquadInit(biquad_t* const biquad)
{
    assert(biquad != NULL);

    for (uint32_t i = 0; i < 3; i++)
    {
        biquad->a[i] = 0.0;
        biquad->b[i] = 0.0;
    }

    for (uint32_t i = 0; i < 2; i++)
    {
        biquad->x[i] = 0.0;
        biquad->y[i] = 0.0;
    }

    biquad->a[0] = 1.0;
}

void BiquadReset(biquad_t* const biquad)
{
    assert(biquad != NULL);

    for (uint32_t i = 0; i < 2; i++)
    {
        biquad->x[i] = 0.0;
        biquad->y[i] = 0.0;
    }
}

void BiquadSetCoefficients(biquad_t* const biquad, double a1, double a2, double b0, double b1, double b2)
{
    assert(biquad != NULL);

    biquad->a[1] = a1;
    biquad->a[2] = a2;

    biquad->b[0] = b0;
    biquad->b[1] = b1;
    biquad->b[2] = b2;
}

void BiquadProcess(biquad_t* const biquad, const double* const in, double* const out, uint32_t count)
{
    assert(biquad != NULL);
    assert(in != NULL);
    assert(out != NULL);

   for (uint32_t i = 0; i < count; i++)
   {
       out[i] = ProcessSample(biquad, in[i]);
   }
}

void BiquadStatePrint(const biquad_t* const biquad)
{
    assert(biquad != NULL);

    printf("Biquad state:\n");
    printf("Biquad x[0]=%f; x[1]=%f\n", biquad->x[0], biquad->x[1]);
    printf("Biquad y[0]=%f; y[1]=%f\n", biquad->y[0], biquad->y[1]);
}

void BiquadCoefficientsPrint(const biquad_t* const biquad)
{
    assert(biquad != NULL);

    printf("Biquad coefficients:\n");
    printf("Biquad a[0]=%f; a[1]=%f; a[2]=%f\n", biquad->a[0], biquad->a[1], biquad->a[2]);
    printf("Biquad b[0]=%f; b[1]=%f; b[2]=%f\n", biquad->b[0], biquad->b[1], biquad->b[2]);
}

