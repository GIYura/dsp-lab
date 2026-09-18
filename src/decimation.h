#ifndef DECIMATION_H
#define DECIMATION_H

#include <stdint.h>

void Decimate(const double* const src, double* const dst, uint32_t size, uint32_t factor);

#endif /* DECIMATION_H */
