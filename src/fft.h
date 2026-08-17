#ifndef FFT_H
#define FFT_H

#include <stdint.h>

#include "complex.h"

/* Brief: Calculate FFT
* [in] - samples - pointer to samples storage
* [in] - spectrum - pointer to spectrum storage
* [in] - count - samples counter
* [out] - none
* */
void FFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count);

/* Brief: Generate FFT bins
* [in] - bins - pointer to bin storage
* [in] - count - bin counter
* [out] - none
* */
void FFT_GenerateBins(bin_t* const bins, uint16_t count);

/* Brief: Calculate FFT raw (unnormalized) magnitude
* [in] - spectrum - pointer to spectrum storage
* [out] - value
* */
double FFT_CalculateRawMagnitude(const complex_t* const spectrum);

/* Brief: Print FFT
* [in] - bins - pointer to bin storage
* [in] - spectrum - pointer to spectrum storage
* [in] - count - bin counter
* [out] - value
* */
void FFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count);

#endif /* FFT_H */
