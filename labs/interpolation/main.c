/*
 * Interpolation demo
 * */

#include "config.h"
#include "save.h"
#include "signal.h"
#include "interpolation.h"
#include "dft.h"
#include "fir.h"
#include "window.h"
#include "convolution.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (4000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define INTERPOLATION_FACTOR    (2U)
#define INTERPOLATED_COUNT      (SAMPLE_COUNT * INTERPOLATION_FACTOR)
#define INTERPOLATED_SAMPLE_HZ  (FREQ_SAMPLE_HZ * INTERPOLATION_FACTOR)
#define FIR_TAP_COUNT           (31U)
#define CONV_SIZE               (INTERPOLATED_COUNT + FIR_TAP_COUNT - 1U)
#define LPF_CUT_OFF_HZ          (2000.0)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    double samplesZeroStuffed[INTERPOLATED_COUNT] = {0};
    bin_t bins[DFT_SIZE];
    bin_t binsZeroStuffed[INTERPOLATED_COUNT];
    bin_t binsInterpolated[CONV_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    complex_t spectrumInterpolated[CONV_SIZE];
    complex_t spectrumZeroStuffed[INTERPOLATED_COUNT];
    complex_t shiftedSpectrumInterpolated[CONV_SIZE];
    complex_t shiftedSpectrumZeroStuffed[INTERPOLATED_COUNT];
    double coefficients[FIR_TAP_COUNT];
    double window[FIR_TAP_COUNT];
    double windowed[FIR_TAP_COUNT];
    double normalized[FIR_TAP_COUNT];
    double samplesConvoluted[CONV_SIZE];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    /* Low pass filter and window */
    FIR_LowPassGenerate(coefficients, FIR_TAP_COUNT, INTERPOLATED_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    WindowGenerate(WINDOW_HANN, window, FIR_TAP_COUNT);
    WindowApply(coefficients, window, windowed, FIR_TAP_COUNT);
    FIR_Normalize(windowed, normalized, FIR_TAP_COUNT, INTERPOLATION_FACTOR);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("dft_spectrum_orig.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply zero-stuff to initial samples */
    Interpolate(samples, SAMPLE_COUNT, samplesZeroStuffed, INTERPOLATED_COUNT, INTERPOLATION_FACTOR);

    /* Calculate DFT of zero-stuffed array */
    DFT_GenerateBins(binsZeroStuffed, INTERPOLATED_COUNT, INTERPOLATED_SAMPLE_HZ);
    DFT_Calculate(samplesZeroStuffed, spectrumZeroStuffed, INTERPOLATED_COUNT);
    DFT_ShiftSpectrum(spectrumZeroStuffed, shiftedSpectrumZeroStuffed, INTERPOLATED_COUNT);
    SaveSpectrumDat("dft_spectrum_zero_stuffed.dat", binsZeroStuffed, shiftedSpectrumZeroStuffed, DFT_CalculateRawMagnitude, INTERPOLATED_COUNT);

    /* Apply convolution to zero-stuffed array */
    Convolution(samplesZeroStuffed, samplesConvoluted, normalized, INTERPOLATED_COUNT, FIR_TAP_COUNT);

    /* Calculate DFT of convoluted array */
    DFT_GenerateBins(binsInterpolated, INTERPOLATED_COUNT, INTERPOLATED_SAMPLE_HZ);
    DFT_Calculate(samplesConvoluted, spectrumInterpolated, INTERPOLATED_COUNT);
    DFT_ShiftSpectrum(spectrumInterpolated, shiftedSpectrumInterpolated, INTERPOLATED_COUNT);

    SaveSpectrumDat("dft_spectrum_interpolated.dat", binsInterpolated, shiftedSpectrumInterpolated, DFT_CalculateRawMagnitude, INTERPOLATED_COUNT);

    SaveTimeDat("zero_stuffed.dat", samplesZeroStuffed, INTERPOLATED_COUNT, INTERPOLATED_SAMPLE_HZ);
    SaveTimeDat("filtered.dat", samplesConvoluted, CONV_SIZE, INTERPOLATED_SAMPLE_HZ);

    return 0;
}
