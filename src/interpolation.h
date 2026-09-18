#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stdint.h>

void Interpolate(const double* const src, uint32_t srcSize, double* const dst, uint32_t dstSize, uint32_t factor);

#endif /* INTERPOLATION_H */
