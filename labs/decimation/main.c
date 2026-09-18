/*
 * Decimation demo
 * */

#include "config.h"
#include "save.h"
#include "signal.h"
#include "decimation.h"
#include "dft.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (8000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define DECIMATION_FACTOR       (2U)
#define DECIMATED_COUNT         (SAMPLE_COUNT / DECIMATION_FACTOR)
#define DECIMATED_SAMPLE_HZ     (FREQ_SAMPLE_HZ / DECIMATION_FACTOR)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    double decimated[DECIMATED_COUNT] = {0};
    bin_t bins[DFT_SIZE];
    bin_t binsDecimated[DECIMATED_COUNT];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    complex_t spectrumDecimated[DECIMATED_COUNT];
    complex_t shiftedSpectrumDecimated[DECIMATED_COUNT];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    SaveTimeDat("orig.dat", samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);

    SaveSpectrumDat("dft_spectrum_1.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply decimation */
    Decimate(samples, decimated, SAMPLE_COUNT, DECIMATION_FACTOR);

    DFT_GenerateBins(binsDecimated, DECIMATED_COUNT, DECIMATED_SAMPLE_HZ);
    DFT_Calculate(decimated, spectrumDecimated, DECIMATED_COUNT);
    DFT_ShiftSpectrum(spectrumDecimated, shiftedSpectrumDecimated, DECIMATED_COUNT);

    SaveSpectrumDat("dft_spectrum_2.dat", binsDecimated, shiftedSpectrumDecimated, DFT_CalculateRawMagnitude, DECIMATED_COUNT);

    SaveTimeDat("decimated.dat", decimated, DECIMATED_COUNT, DECIMATED_SAMPLE_HZ);

    return 0;
}
