/*
 * Decimation demo
 * */

#include "config.h"
#include "save.h"
#include "signal.h"
#include "decimation.h"
#include "dft.h"
#include "window.h"
#include "convolution.h"
#include "fir.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (8000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define DECIMATION_FACTOR       (2U)
#define DECIMATED_COUNT         (SAMPLE_COUNT / DECIMATION_FACTOR)
#define DECIMATED_SAMPLE_HZ     (FREQ_SAMPLE_HZ / DECIMATION_FACTOR)
#define FIR_TAP_COUNT           (31U)
#define CONV_SIZE               (SAMPLE_COUNT + FIR_TAP_COUNT - 1U)
#define LPF_CUT_OFF_HZ          (2000.0)

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
    double coefficients[FIR_TAP_COUNT];
    double window[FIR_TAP_COUNT];
    double windowed[FIR_TAP_COUNT];
    double normalized[FIR_TAP_COUNT];
    double samplesConvoluted[CONV_SIZE];

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 1.0, 0.0);

    /* Low pass filter and window */
    FIR_LowPassGenerate(coefficients, FIR_TAP_COUNT, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    WindowGenerate(WINDOW_HANN, window, FIR_TAP_COUNT);
    WindowApply(coefficients, window, windowed, FIR_TAP_COUNT);
    FIR_Normalize(windowed, normalized, FIR_TAP_COUNT, 1);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("dft_spectrum_orig.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply anti-aliasing LPF */
    Convolution(samples, samplesConvoluted, normalized, SAMPLE_COUNT, FIR_TAP_COUNT);

    /* Apply decimation */
    Decimate(samplesConvoluted, decimated, SAMPLE_COUNT, DECIMATION_FACTOR);

    DFT_GenerateBins(binsDecimated, DECIMATED_COUNT, DECIMATED_SAMPLE_HZ);
    DFT_Calculate(decimated, spectrumDecimated, DECIMATED_COUNT);
    DFT_ShiftSpectrum(spectrumDecimated, shiftedSpectrumDecimated, DECIMATED_COUNT);
    SaveSpectrumDat("dft_spectrum_decimated.dat", binsDecimated, shiftedSpectrumDecimated, DFT_CalculateRawMagnitude, DECIMATED_COUNT);

    return 0;
}
