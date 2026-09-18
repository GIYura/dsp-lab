/*
 * DFT demo
 * */

#include "config.h"
#include "dft.h"
#include "save.h"
#include "signal.h"

/* Demo config */
#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE] = {0};
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];

    /* Print demo settings */
    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, DFT_SIZE);

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    /* Calculate DFT */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);

    /* Save into files for plot */
    SaveDat("input.dat", samples, DFT_SIZE);
    SaveSpectrumDat("dft_spectrum.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
