#include "config.h"
#include "convolution.h"
#include "output.h"
#include "signal.h"

#define IMPULSE_RESPONSE_SIZE (3U)
#define DEMO_CONV_SIZE (SAMPLE_COUNT + IMPULSE_RESPONSE_SIZE - 1U)

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    const double impulse_response[IMPULSE_RESPONSE_SIZE] = {0.25, 0.5, 0.25};
    double result[DEMO_CONV_SIZE];

    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.5, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    Convolution(samples, result, impulse_response, SAMPLE_COUNT, IMPULSE_RESPONSE_SIZE);

    SaveDat("input.dat", samples, SAMPLE_COUNT);
    SaveDat("impulse_response.dat", impulse_response, IMPULSE_RESPONSE_SIZE);
    SaveDat("convolution.dat", result, DEMO_CONV_SIZE);

    return 0;
}
