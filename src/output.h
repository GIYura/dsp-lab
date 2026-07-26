#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>

#include "dft.h"

/* Brief: Save window function into .dat file
* [in] - samples - pointer to samples storage
* [in] - count - samples counter
* [out] - none
* */
void SaveWindowDat(const double* samples, uint16_t count);

/* Brief: Save windowed samples into .dat file
* [in] - samples - pointer to samples storage
* [in] - count - samples counter
* [out] - none
* */
void SaveWindowedSignalDat(const double* samples, uint16_t count);

/* Brief: Save input signal into .dat file
* [in] - samples - pointer to samples storage
* [in] - count - samples counter
* [out] - none
* */
void SaveInputDat(const double* samples, uint16_t count);

/* Brief: Save spectrum into .dat file
* [in] - bins - pointer to bin storage
* [in] - spectrum - pointer to spectrum storage
* [in] - count - bin counter
* [out] - none
* */
void SaveSpectrumDat(const bin_t* bins,const complex_t* spectrum, uint16_t count);

#endif /* OUTPUT_H */
