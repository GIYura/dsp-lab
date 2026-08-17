#include "config.h"
#include "dft.h"
#include "output.h"
#include "signal.h"

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE] = {0};
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];

    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, DFT_SIZE);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    SignalZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    DFT_GenerateBins(bins, DFT_SIZE);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_Print(bins, spectrum, DFT_SIZE);

    SaveDat("input.dat", samples, DFT_SIZE);
    SaveSpectrumDat("dft_spectrum.dat", bins, spectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
