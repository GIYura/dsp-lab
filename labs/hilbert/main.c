/*
 * Hilbert Transform demo
 * */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "fir.h"
#include "signal.h"
#include "config.h"
#include "save.h"
#include "convolution.h"
#include "dft.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (8000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define HILBERT_COEFF_COUNT     (31u)
#define HILBERT_CONV_SIZE       (SAMPLE_COUNT + HILBERT_COEFF_COUNT - 1U)
#define HILBERT_DELAY           ((HILBERT_COEFF_COUNT - 1U) / 2U)

int main(void)
{
    /* LOcal variables */
    double coeff[HILBERT_COEFF_COUNT];
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT];
    double samplesDelay[HILBERT_CONV_SIZE] = {0};
    double samplesConvoluted[HILBERT_CONV_SIZE];
    complex_t iq[SAMPLE_COUNT];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    bin_t bins[DFT_SIZE];

    /* Create initial signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveDat("cos.dat", samples, DFT_SIZE);

    /* Generate coefficients */
    FIR_HilbertGenerate(coeff, HILBERT_COEFF_COUNT);

    /* Apply convolution */
    Convolution(samples, samplesConvoluted, coeff, SAMPLE_COUNT, HILBERT_COEFF_COUNT);
    SaveDat("sin.dat", samplesConvoluted, HILBERT_CONV_SIZE);

    /* Delay initial signal */
    SignalSamplesDelay(samples, SAMPLE_COUNT, samplesDelay, HILBERT_CONV_SIZE, HILBERT_DELAY);
    SaveDat("cos_delay.dat", samplesDelay, HILBERT_CONV_SIZE);

    /* Create IQ signal */
    SignalCreateIQSamples(samplesDelay, samplesConvoluted, iq, SAMPLE_COUNT, HILBERT_DELAY);

    /* Create spectrum */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_CalculateComplex(iq, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("dft_iq_spectrum.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
