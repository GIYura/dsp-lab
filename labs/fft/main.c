#include "config.h"
#include "fft.h"
#include "output.h"
#include "signal.h"

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[FFT_SIZE] = {0};
    bin_t bins[FFT_SIZE];
    complex_t spectrum[FFT_SIZE];

    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, DFT_SIZE);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    SignalZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    FFT_GenerateBins(bins, FFT_SIZE);
    FFT_Calculate(samples, spectrum, FFT_SIZE);
    FFT_Print(bins, spectrum, FFT_SIZE);

    SaveDat("input.dat", samples, FFT_SIZE);
    SaveSpectrumDat("fft_spectrum.dat", bins, spectrum, FFT_CalculateRawMagnitude, FFT_SIZE);

    return 0;
}
