/*
 * FFT demo
 **/

#include "config.h"
#include "fft.h"
#include "save.h"
#include "signal.h"

/* Demo config */
#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define FFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[FFT_SIZE] = {0};
    bin_t bins[FFT_SIZE];
    complex_t spectrum[FFT_SIZE];
    complex_t shiftedSpectrum[FFT_SIZE];

    /* Print demo settings */
    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, FFT_SIZE);

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    /* Calculate FFT */
    FFT_GenerateBins(bins, FFT_SIZE, FREQ_SAMPLE_HZ);
    FFT_Calculate(samples, spectrum, FFT_SIZE);
    FFT_ShiftSpectrum(spectrum, shiftedSpectrum, FFT_SIZE);
    FFT_Print(bins, shiftedSpectrum, FFT_SIZE);

    /* Save into files for plot */
    SaveDat("input.dat", samples, FFT_SIZE);
    SaveSpectrumDat("fft_spectrum.dat", bins, shiftedSpectrum, FFT_CalculateRawMagnitude, FFT_SIZE);

    return 0;
}
