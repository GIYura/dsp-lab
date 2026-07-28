#ifndef FIR_H
#define FIR_H

#include <stdint.h>
#include <stdbool.h>

/* Brief: Generate ideal LPF impulse response
* [in] - coefficients - pointer to coefficients storage
* [in] - tapCount - FIR size
* [in] - sampleRateHz - sample rate, Hz
* [in] - cutofHz - LPF cutoff frequency, Hz
* [out] - none
* */
void FIR_LowPassGenerate(double* coefficients, uint32_t tapCount, double sampleRateHz, double cutoffHz);

/* Brief: Generate normalized LPF impulse response
* [in] - src - pointer to ideal coefficients storage
* [in] - dst - pointer to normalized coefficients storage
* [in] - size - storage size
* [out] - none
* */
void FIR_Normalize(const double* const src, double* const dst, uint32_t size);

#endif /* FIR_H */
