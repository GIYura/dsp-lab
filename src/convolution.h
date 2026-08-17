#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <stdint.h>

/* Brief: Convolution
* [in] - src - pointer to source storage
* [in] - dst - pointer to destination storage
* [in] - impulseResponce - pointer to impulse response characteristic
* [in] - srcLen - source length
* [in] - impulseResponseLen - impulse response length
* [out] - value
* */
void Convolution(const double* const src, double* const dst, const double* const impulseResponse, uint32_t srcLen, uint32_t impulseResponseLen);

#endif /* CONVOLUTION_H */
