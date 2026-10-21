#ifndef IIR_H
#define IIR_H

#include <stdint.h>

typedef struct
{
    double a;       /* Feedforward coefficient */
    double b;       /* Feedback coefficient */
    double y;       /* Previous output sample: y[n-1] */
} IIR_First_Order_t;

typedef struct
{
    double a;       /* Feedforward coefficient */
    double b[2];    /* Feedback coefficients */
    double y[2];    /* Previous outputs: y[0] = y[n-1], y[1] = y[n-2] */
} IIR_Second_Order_t;

/*
* Brief: Initialize first-order IIR (coefficients and state)
*
* [in] filter - pointer to filter storage
* */
void IIR_FirstOrderInit(IIR_First_Order_t* const filter);

/*
* Brief: Generate first-order IIR low-pass filter coefficients.
*        The filter has unity DC gain and -3 dB magnitude
*        at the specified cutoff frequency.
*
* [in] filter - pointer to filter storage
* [in] sampleRateHz - sampling frequency, Hz
* [in] cutoffHz - cutoff frequency, Hz
*/
void IIR_FirstOrderLowPassGenerate(IIR_First_Order_t* const filter, double sampleRateHz, double cutoffHz);

/*
* Brief: Filter input samples using a first-order IIR filter.
*
* [in] filter - filter coefficients and internal state
* [in] samples - input samples
* [in] output - filtered output samples
* [in] size - number of samples
*/
void IIR_FirstOrderCalculate(IIR_First_Order_t* const filter, const double* const samples, double* output, uint32_t size);

/*
* Brief: Print first-order IIR coefficients
*
* [in] - filter - pointer to filter storage
* */
void IIR_FirstOrderPrint(const IIR_First_Order_t* const filter);

/*
* Brief: Calculate first-order IIR filter magnitude-frequency characteristics
*
* [in] - filter - pointer to filter storage
* [in] - outFreq - pointer to frequency storage, Hz
* [in] - outMagnitude - pointer to magnitude storage
* [in] - sampleRateHz - sample rate, Hz
* [in] - size - number of frequency points
* [out] - none
* */
void IIR_FirstOrderMagnitudeResponse(const IIR_First_Order_t* const filter, double* const outFreq, double* const outMagnitude, double sampleRateHz, uint32_t size);

/*
* Brief: Initialize second-order IIR filter (coefficients and state)
* [in] - filter - pointer to filter storage
* */
void IIR_SecondOrderInit(IIR_Second_Order_t* const filter);

/*
* Brief: Generate second-order IIR low-pass filter coefficients.
*        The filter is equivalent to two cascaded identical
*        first-order low-pass sections.
*        The overall response has unity DC gain and -3 dB
*        magnitude at the specified cutoff frequency.
*
* [in] filter - pointer to filter storage
* [in] sampleRateHz - sampling frequency, Hz
* [in] cutoffHz - cutoff frequency, Hz
*/
void IIR_SecondOrderLowPassGenerate(IIR_Second_Order_t* const filter, double sampleRateHz, double cutoffHz);

/*
* Brief: Apply second-order IIR filter coefficients to input samples
*
* [in] - filter - pointer to filter storage
* [in] - samples - pointer to samples storage
* [in] - output - pointer to output storage
* [in] - size - number of samples
* [out] - none
* */
void IIR_SecondOrderCalculate(IIR_Second_Order_t* const filter, const double* const samples, double* output, uint32_t size);

/*
* Brief: Print second-order IIR filter coefficients
*
* [in] - filter - pointer to filter storage
* [out] - none
* */
void IIR_SecondOrderPrint(const IIR_Second_Order_t* const filter);

/*
* Brief: Calculate IIR filter magnitude-frequency characteristics
*
* [in] - filter - pointer to filter storage
* [in] - outFreq - pointer to frequency storage
* [in] - outMagnitude - pointer to magnitude storage
* [in] - sampleRateHz - sample rate, Hz
* [in] - size - number of frequency points
* [out] - none
* */
void IIR_SecondOrderMagnitudeResponse(const IIR_Second_Order_t* const filter, double *outFreq, double *outMagnitude, double sampleRateHz, uint32_t size);

#endif /* IIR_H */
