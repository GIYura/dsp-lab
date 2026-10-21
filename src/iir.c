#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "iir.h"
#include "config.h"

/* NOTE:
 * Разностное уравнение: y[n] = a * x[n] + b * y[n - 1] - это БИХ-фильтр первого порядка
 * a — feedforward: вклад текущего входного отсчёта.
 * b — feedback: вклад предыдущего выходного отсчёта.
 * Коэффициент b выбран так, чтобы собственный отклик цифрового фильтра затухал с той же постоянной времени,
 * что и у соответствующего аналогового RC-фильтра.
 * */

/*
 * IIR First Order
 * */

void IIR_FirstOrderInit(IIR_First_Order_t* const filter)
{
    assert(filter != NULL);

    filter->a = 0.0;
    filter->b = 0.0;
    filter->y = 0.0;
}

void IIR_FirstOrderLowPassGenerate(IIR_First_Order_t *const filter, double sampleRateHz, double cutoffHz)
{
    assert(filter != NULL);
    assert(sampleRateHz > 0.0);
    assert(cutoffHz > 0.0);
    assert(cutoffHz < sampleRateHz / 2.0);

    double omega;
    double c;
    double t;

    omega = (2.0 * PI * cutoffHz) / sampleRateHz;

    c = cos(omega);

    t = 2.0 - c;

    filter->b = t - sqrt(t * t - 1.0);
    filter->a = 1.0 - filter->b;
}

void IIR_FirstOrderCalculate(IIR_First_Order_t* const filter, const double* const samples, double* output, uint32_t size)
{
    assert(filter != NULL);
    assert(samples != NULL);
    assert(output != NULL);

    for (uint32_t i = 0; i < size; i++)
    {
        filter->y = filter->a * samples[i] + filter->b * filter->y;
        output[i] = filter->y;
    }
}

void IIR_FirstOrderPrint(const IIR_First_Order_t* const filter)
{
    assert(filter != NULL);

    printf("IIR First order a=%f b=%f\n", filter->a, filter->b);
}

void IIR_FirstOrderMagnitudeResponse(const IIR_First_Order_t* const filter, double* const outFreq, double* const outMagnitude, double sampleRateHz, uint32_t size)
{
    assert(filter != NULL);
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

        denominatorReal = 1.0 - filter->b * zInvReal;
        denominatorImag = zInvImag * (-filter->b);

        magnitude = fabs(filter->a) / sqrt(denominatorReal * denominatorReal + denominatorImag * denominatorImag);

        outFreq[i] = freqHz;
        outMagnitude[i] = magnitude;
    }
}

/*
 * IIR Second Order
 * */
void IIR_SecondOrderInit(IIR_Second_Order_t* const filter)
{
    assert(filter != NULL);

    filter->a = 0.0;

    filter->b[0] = 0.0;
    filter->b[1] = 0.0;

    filter->y[0] = 0.0;
    filter->y[1] = 0.0;
}

void IIR_SecondOrderLowPassGenerate(IIR_Second_Order_t* const filter, double sampleRateHz, double cutoffHz)
{
    assert(filter != NULL);
    assert(sampleRateHz > 0.0);
    assert(cutoffHz > 0.0);
    assert(cutoffHz < sampleRateHz / 2.0);

    double omega;
    double k;
    double c;
    double p;

    omega = 2.0 * PI * cutoffHz / sampleRateHz;
    k = sqrt(2.0) - 1.0;
    c = cos(omega);
    p = (1.0 + k - c - sqrt((1.0 + k - c) * (1.0 + k - c) - k * k)) / k;

    filter->a = (1.0 - p) * (1.0 - p);
    filter->b[0] = 2.0 * p;
    filter->b[1] = -p * p;
}

void IIR_SecondOrderCalculate(IIR_Second_Order_t* const filter, const double* const samples, double* output, uint32_t size)
{
    assert(filter != NULL);
    assert(samples != NULL);
    assert(output != NULL);

    double y = 0.0;

    for (uint32_t i = 0; i < size; i++)
    {
        y = filter->a * samples[i] + filter->b[0] * filter->y[0] + filter->b[1] * filter->y[1];

        filter->y[1] = filter->y[0];
        filter->y[0] = y;

        output[i] = y;
    }
}

void IIR_SecondOrderPrint(const IIR_Second_Order_t* const filter)
{
    assert(filter != NULL);

    printf("IIR Second order a=%f b0=%f b1=%f\n", filter->a, filter->b[0], filter->b[1]);
}

void IIR_SecondOrderMagnitudeResponse(const IIR_Second_Order_t* const filter, double *outFreq, double *outMagnitude, double sampleRateHz, uint32_t size)
{
    assert(filter != NULL);
    assert(outFreq != NULL);
    assert(outMagnitude != NULL);

    double freqHz;
    double deltaFreq;
    double omega;
    double zInvReal[2];
    double zInvImag[2];

    double denominatorReal;
    double denominatorImag;
    double magnitude;

    deltaFreq = sampleRateHz / size;

    for (uint32_t i = 0; i <= size / 2; i++)
    {
        freqHz = (double)i * deltaFreq;

        omega = 2.0 * PI * freqHz / sampleRateHz;

        zInvReal[0] = cos(omega);
        zInvImag[0] = -sin(omega);

        zInvReal[1] = cos(2 * omega);
        zInvImag[1] = -sin(2 * omega);

        denominatorReal = 1.0 - filter->b[0] * zInvReal[0] - filter->b[1] * zInvReal[1];
        denominatorImag = (-filter->b[0]) * zInvImag[0] - filter->b[1] * zInvImag[1];

        magnitude = fabs(filter->a) / sqrt(denominatorReal * denominatorReal + denominatorImag * denominatorImag);

        outFreq[i] = freqHz;
        outMagnitude[i] = magnitude;
    }
}
