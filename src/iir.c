#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "iir.h"

/* NOTE:
 * Разностное уравнение: y[n] = a * x[n] + b * y[n - 1] - это БИХ-фильтр первого порядка
 * a — feedforward: вклад текущего входного отсчёта.
 * b — feedback: вклад предыдущего выходного отсчёта.
 * Коэффициент b выбран так, чтобы собственный отклик цифрового фильтра затухал с той же постоянной времени,
 * что и у соответствующего аналогового RC-фильтра.
 * */

void IIR_LowPassGenerate(iir_t* const filter, double sampleRateHz, double cutoffHz)
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

    for (uint32_t i = 0; i < size; i++)
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

void IIR_Z_Transform(double a, double b, double* const outFreq, double* const outMagnitude, double sampleRateHz, uint32_t size)
{
    assert(outFreq != NULL);
    assert(outMagnitude != NULL);

    double freqHz;
    double deltaFreq;
    double omega;
    double zInvReal;
    double zInvImag;
    double denominatorReal;
    double denominatorImag;
    double magnitude;

    deltaFreq = sampleRateHz / size;

    for (uint32_t i = 0; i <= size / 2; i++)
    {
        freqHz = (double)i * deltaFreq;

        omega = 2.0 * PI * freqHz / sampleRateHz;

        zInvReal = cos(omega);
        zInvImag = -sin(omega);

        denominatorReal = 1.0 - b * zInvReal;
        denominatorImag = zInvImag * (-b);

        magnitude = fabs(a) / sqrt(denominatorReal * denominatorReal + denominatorImag * denominatorImag);

        outFreq[i] = freqHz;
        outMagnitude[i] = magnitude;
    }
}


