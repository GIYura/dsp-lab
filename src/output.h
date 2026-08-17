#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>

#include "config.h"
#include "complex.h"

typedef double (*fp_t)(const complex_t* const value);

/* Brief: Save spectrum into .dat file
* [in] - fileName - pointer to file name
* [in] - bins - pointer to bin storage
* [in] - spectrum - pointer to spectrum storage
* [in] - callback - pointer to function
* [in] - count - bin counter
* [out] - none
* */
void SaveSpectrumDat(const char* const fileName, const bin_t* bins, const complex_t* spectrum, fp_t cb, uint16_t count);

/* Brief: Generic save into .dat file
* [in] - fileName - pointer to file name
* [in] - in - pointer to input storage
* [in] - count - size of input storage
* [out] - none
* */
void SaveDat(const char* const fileName, const double* const in, uint32_t count);

#endif /* OUTPUT_H */
