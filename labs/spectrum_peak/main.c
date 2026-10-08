/*
 * Spectrum peak
 * */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "config.h"
#include "dft.h"
#include "save.h"
#include "signal.h"
#include "complex.h"

/* Demo config */
#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (8U + ZERO_PADDING_COUNT)

static double SpectrumPeak(const complex_t* const spectrum, double sampleFreqHz, uint32_t size)
{
    assert(spectrum != NULL);
    assert(size > 0);

    double maxMagnitude = 0.0;
    double magnitude = 0.0;
    uint32_t peakIndex;
    complex_t m_k;
    complex_t m_k_prev;
    complex_t m_k_next;
    complex_t numerator;
    complex_t denominator;
    complex_t sigma;
    complex_t coeff;
    double m_peak;
    double f_peak;

    coeff.real = 2.0;
    coeff.imag = 0.0;

    for (uint32_t i = 0; i < size; i++)
    {
        magnitude = DFT_CalculateRawMagnitude(&spectrum[i]);
        if (magnitude > maxMagnitude)
        {
            maxMagnitude = magnitude;
            peakIndex = i;
        }
    }

    m_k_prev = spectrum[peakIndex - 1];
    m_k_next = spectrum[peakIndex + 1];
    m_k = spectrum[peakIndex];

    numerator = ComplexSub(m_k_next, m_k_prev);
    m_k = ComplexMul(coeff, m_k);
    denominator = ComplexSub(m_k, m_k_prev);
    denominator = ComplexSub(denominator, m_k_next);

    sigma = ComplexDiv(numerator, denominator);

    m_peak = peakIndex - sigma.real;
    f_peak = m_peak * (sampleFreqHz / size);

    return f_peak;
}

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE] = {0};
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    double freqPeak;
    double freqDesired = 1550.0;
    double freqDelta;

    /* Print demo settings */
    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, DFT_SIZE);

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, freqDesired, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    /* Calculate DFT */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum, DFT_SIZE);

    freqPeak = SpectrumPeak(spectrum, FREQ_SAMPLE_HZ, DFT_SIZE);
    printf("\nFreq peak=%f Hz; Freq desired=%f Hz\n", freqPeak, freqDesired);
    if (freqPeak > freqDesired)
    {
        freqDelta = freqPeak - freqDesired;
    }
    else
    {
        freqDelta = freqDesired - freqPeak;
    }

    printf("Freq delta=%f Hz; value=%f%%\n\n", freqDelta, (freqDelta / 100));

    return 0;
}
