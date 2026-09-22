#ifndef NOISE_H
#define NOISE_H

#include <stdint.h>

void NoiseGenerate(double* const noise, uint32_t count, double amplitude);
void NoiseAdd(const double* const in, const double* const noise, double* const out, uint32_t count);

#endif /* NOISE_H */
