/*
 * Spectrum scale demo
 * */

#include <math.h>

#include "config.h"
#include "dft.h"
#include "save.h"
#include "signal.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (8000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define FULL_SCALE_AMPLITUDE    (1.0)
#define DBFS_FLOOR              (-120.0)

static double CalculateDbfs(const complex_t* const sample)
{
    double magnitude = DFT_CalculateRawMagnitude(sample);
    double dbfs;

    if (magnitude <= 0.0)
    {
        return DBFS_FLOOR;
    }

    dbfs = 20.0 * log10(magnitude / FULL_SCALE_AMPLITUDE);

    if (dbfs < DBFS_FLOOR)
    {
        dbfs = DBFS_FLOOR;
    }

    return dbfs;
}

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE] = {0};
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.5, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.1, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    /* Calculate DFT */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    DFT_SpectrumNormalize(shiftedSpectrum, DFT_SIZE);

    /* Save into files for plot */
    SaveSpectrumDat("dft_spectrum.dat", bins, shiftedSpectrum, CalculateDbfs, DFT_SIZE);

    return 0;
}
