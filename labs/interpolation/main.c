/*
 * Interpolation demo
 * */

#include "config.h"
#include "save.h"
#include "signal.h"
#include "interpolation.h"
#include "dft.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (4000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define INTERPOLATION_FACTOR    (2U)
#define INTERPOLATED_COUNT      (SAMPLE_COUNT * INTERPOLATION_FACTOR)
#define INTERPOLATED_SAMPLE_HZ  (FREQ_SAMPLE_HZ * INTERPOLATION_FACTOR)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    double interpolated[INTERPOLATED_COUNT] = {0};
    bin_t bins[DFT_SIZE];
    bin_t binsInterpolated[INTERPOLATED_COUNT];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    complex_t spectrumInterpolated[INTERPOLATED_COUNT];
    complex_t shiftedSpectrumInterpolated[INTERPOLATED_COUNT];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    SaveTimeDat("orig.dat", samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);

    SaveSpectrumDat("dft_spectrum_1.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply interpolation */
    Interpolate(samples, SAMPLE_COUNT, interpolated, INTERPOLATED_COUNT, INTERPOLATION_FACTOR);

    DFT_GenerateBins(binsInterpolated, INTERPOLATED_COUNT, INTERPOLATED_SAMPLE_HZ);
    DFT_Calculate(interpolated, spectrumInterpolated, INTERPOLATED_COUNT);
    DFT_ShiftSpectrum(spectrumInterpolated, shiftedSpectrumInterpolated, INTERPOLATED_COUNT);

    SaveSpectrumDat("dft_spectrum_2.dat", binsInterpolated, shiftedSpectrumInterpolated, DFT_CalculateRawMagnitude, INTERPOLATED_COUNT);

    SaveTimeDat("interpolated.dat", interpolated, INTERPOLATED_COUNT, INTERPOLATED_SAMPLE_HZ);

    return 0;
}
