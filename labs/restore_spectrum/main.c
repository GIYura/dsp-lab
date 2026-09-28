/*
 * Restore demo
 * */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "config.h"
#include "dft.h"
#include "signal.h"

#define FREQ_SAMPLE_HZ      (8000.0)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

static void CreatePackedSequence(const double* const src1, const double* const src2, complex_t* const dst, uint32_t size)
{
    assert(src1 != NULL);
    assert(src2 != NULL);
    assert(dst != NULL);
    assert(size > 0);

    for (uint32_t i = 0; i < size; i++)
    {
        dst[i].real = src1[i];
        dst[i].imag = src2[i];
    }
}

static void RestoreSequenceA(const complex_t* const packed, complex_t* const restored, uint32_t size)
{
    assert(packed != NULL);
    assert(restored != NULL);
    assert(size > 0);
    uint32_t mirror;
    complex_t x;
    complex_t x_mirror;

    for (uint32_t k = 0; k < size; k++)
    {
        mirror = (size - k) % size;

        x = packed[k];
        x_mirror = packed[mirror];

        /* Complex conjugate of X[N-k] */
        x_mirror.imag = -x_mirror.imag;

        /* A[k] = (X[k] + X*[N-k]) / 2 */
        restored[k].real = (x.real + x_mirror.real) / 2.0;
        restored[k].imag = (x.imag + x_mirror.imag) / 2.0;
    }
}

static void RestoreSequenceB(const complex_t* const packed, complex_t* const restored, uint32_t size)
{
    assert(packed != NULL);
    assert(restored != NULL);
    assert(size > 0);
    uint32_t mirror;
    complex_t x;
    complex_t x_mirror;
    double diff_real;
    double diff_imag;

    for (uint32_t k = 0; k < size; k++)
    {
        mirror = (size - k) % size;

        x = packed[k];
        x_mirror = packed[mirror];

        /* X*[N-k] */
        x_mirror.imag = -x_mirror.imag;

        /*
         * diff = X[k] - X*[N-k]
         * diff = 2jB[k]
         */
        diff_real = x.real - x_mirror.real;
        diff_imag = x.imag - x_mirror.imag;

        /*
         * B[k] = (-j / 2) * diff
         *
         * (R + jI) * (-j) = I - jR
         */
        restored[k].real =  diff_imag / 2.0;
        restored[k].imag = -diff_real / 2.0;
    }
}

int main(void)
{
    /* Local variables */
    bin_t bins[DFT_SIZE];

    harmonic_t signal_a[HARMONIC_COUNT] = {0};
    double samples_a[DFT_SIZE] = {0};
    complex_t spectrum_a[DFT_SIZE];
    complex_t shiftedSpectrum_a[DFT_SIZE];

    harmonic_t signal_b[HARMONIC_COUNT] = {0};
    double samples_b[DFT_SIZE] = {0};
    complex_t spectrum_b[DFT_SIZE];
    complex_t shiftedSpectrum_b[DFT_SIZE];

    complex_t packed[DFT_SIZE];
    complex_t spectrumPacked[DFT_SIZE];

    complex_t restored_a[DFT_SIZE];
    complex_t restored_b[DFT_SIZE];
    complex_t shiftedRestored_a[DFT_SIZE];
    complex_t shiftedRestored_b[DFT_SIZE];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal_a, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal_b, 2000.0, 1.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal_a, HARMONIC_COUNT, samples_a, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SignalGenerateSamples(signal_b, HARMONIC_COUNT, samples_b, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    /* Calculate DFT */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);

    DFT_Calculate(samples_a, spectrum_a, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum_a, shiftedSpectrum_a, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum_a, DFT_SIZE);

    DFT_Calculate(samples_b, spectrum_b, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum_b, shiftedSpectrum_b, DFT_SIZE);
    DFT_Print(bins, shiftedSpectrum_b, DFT_SIZE);

    CreatePackedSequence(samples_a, samples_b, packed, DFT_SIZE);

    DFT_CalculateComplex(packed, spectrumPacked, DFT_SIZE);

    RestoreSequenceA(spectrumPacked, restored_a, DFT_SIZE);
    RestoreSequenceB(spectrumPacked, restored_b, DFT_SIZE);

    DFT_ShiftSpectrum(restored_a, shiftedRestored_a, DFT_SIZE);
    DFT_Print(bins, shiftedRestored_a, DFT_SIZE);

    DFT_ShiftSpectrum(restored_b, shiftedRestored_b, DFT_SIZE);
    DFT_Print(bins, shiftedRestored_b, DFT_SIZE);

    for (uint32_t i = 0; i < DFT_SIZE; i++)
    {
        printf("a.imag=%f; a.real=%f\n", spectrum_a[i].imag, spectrum_a[i].real);
    }

    printf("----------------------\n");

    for (uint32_t i = 0; i < DFT_SIZE; i++)
    {
        printf("r_a.imag=%f; r_a.real=%f\n", restored_a[i].imag, restored_a[i].real);
    }

    printf("----------------------\n");

    for (uint32_t i = 0; i < DFT_SIZE; i++)
    {
        printf("b.imag=%f; b.real=%f\n", spectrum_b[i].imag, spectrum_b[i].real);
    }

    printf("----------------------\n");

    for (uint32_t i = 0; i < DFT_SIZE; i++)
    {
        printf("r_b.imag=%f; r_b.real=%f\n", restored_b[i].imag, restored_b[i].real);
    }

    return 0;
}

