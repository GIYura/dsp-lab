/*
 * I/Q demo
 * */

#include "signal.h"
#include "config.h"
#include "complex.h"
#include "save.h"
#include "dft.h"

/* Demo config */
#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT];
    complex_t iq[SAMPLE_COUNT];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    bin_t bins[DFT_SIZE];

    /* Create signal */
    SignalHarmonicAdd(signal, (-1000.0), 1.0, 0.0);
    SignalHarmonicAdd(signal, (3000.0), 0.0, 0.0);
    SignalHarmonicAdd(signal, (5000.0), 0.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalPrintSamples(samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveDat("real.dat", samples, SAMPLE_COUNT);

    SignalGenerateIQSamples(signal, HARMONIC_COUNT, iq, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalPrintIQSamples(iq, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveIQDat("iq.dat", iq, SAMPLE_COUNT);

    /**/
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_CalculateComplex(iq, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("dft_iq_spectrum.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
