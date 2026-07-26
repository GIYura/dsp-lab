#ifndef DFT_H
#define DFT_H

#include <stdint.h>

#include "complex.h"
#include "config.h"

/* Brief: Calculate DFT
* [in] - samples - pointer to samples storage
* [in] - spectrum - pointer to spectrum storage
* [in] - count - samples counter
* [out] - none
* */
void DFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count);

/* Brief: Generate DFT bins
* [in] - bins - pointer to bin storage
* [in] - count - bin counter
* [out] - none
* */
void DFT_GenerateBins(bin_t* const bins, uint16_t count);

/* Brief: Calculate DFT raw (unnormalized) magnitude
* [in] - spectrum - pointer to spectrum storage
* [out] - value
* */
double DFT_CalculateRawMagnitude(const complex_t* const spectrum);

/* Brief: Print DFT
* [in] - bins - pointer to bin storage
* [in] - spectrum - pointer to spectrum storage
* [in] - count - bin counter
* [out] - value
* */
void DFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count);

#endif /* DFT_H */
