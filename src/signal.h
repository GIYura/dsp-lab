#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    double freqHz;
    double amp;
    double phaseDeg;
} harmonic_t;

/* Brief: Add harmonic into signal
* [in] - harmonic - pointer to harmonic_t struct
* [in] - freqHz - harmonic frequency in Hz
* [in] - amp - harmonic amplitude in volt
* [in] - phaseDeg - harmonic phase in degree
* [out] - true - harmonic added; false - otherwise
* */
bool SignalHarmonicAdd(harmonic_t* harmonic, double freqHz, double amp, double phaseDeg);

/* Brief: Generate descrete samples
* [in] - harmonic - pointer to harmonic_t struct
* [in] - harmCount - harmonic counter
* [in] - samples - pointer to samples storage
* [in] - sampleCount - samples counter
* [out] - none
* */
void SignalGenerateSamples(const harmonic_t* const harmonic, uint8_t harmCount, double* samples, uint16_t sampleCount);

/* Brief: Append zeros to samples
* [in] - samples - pointer to samples storage
* [in] - sampleCount - samples counter
* [in] - zeroCount - zeros counter
* [out] - none
* */
void SignalZeroPadding(double* samples, uint16_t sampleCount, uint16_t zeroCount);

/* Brief: Print signal samples
* [in] - samples - pointer to samples storage
* [in] - count - samples counter
* [out] - none
* */
void SignalPrintSamples(const double* const samples, uint16_t count);

/* Brief: Print signal config
* [in] - harmonic - pointer to harmonic_t struct
* [in] - count - harmonic counter
* [out] - none
* */
void SignalPrintConfig(const harmonic_t* const harmonic, uint16_t count);

#endif /* SIGNAL_H */
