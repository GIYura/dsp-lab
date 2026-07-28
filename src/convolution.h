#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <stdint.h>

void Convolution(const double* const src, double* const dst, const double* const impulseResponse, uint32_t srcLen, uint32_t impulseResponseLen);

#endif /* CONVOLUTION_H */
