/*
 * Spectrum shift demo
 * */

#include "signal.h"
#include "config.h"
#include "complex.h"
#include "save.h"
#include "dft.h"
#include "shift.h"

/* Demo config */
#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    harmonic_t shift[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT];
    complex_t exp[SAMPLE_COUNT];
    complex_t result[SAMPLE_COUNT];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    bin_t bins[DFT_SIZE];

    /* Create signal */
    SignalHarmonicAdd(signal, (+1000.0), 1.0, 0.0);
    SignalHarmonicAdd(signal, (3000.0), 0.0, 0.0);
    SignalHarmonicAdd(signal, (5000.0), 0.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Create shift */
    SignalHarmonicAdd(shift, (-1000.0), 1.0, 0.0);
    SignalHarmonicAdd(shift, (3000.0), 0.0, 0.0);
    SignalHarmonicAdd(shift, (5000.0), 0.0, 0.0);

    SignalGenerateIQSamples(shift, HARMONIC_COUNT, exp, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    /* Apply shift to input signal */
    SignalShift(samples, exp, result, SAMPLE_COUNT);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_CalculateComplex(result, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("shifted_spectrum.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
