/*
 * FIR demo
 * */

#include "config.h"
#include "fir.h"
#include "save.h"
#include "window.h"
#include "signal.h"
#include "dft.h"
#include "convolution.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (16000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define FIR_TAP_COUNT           (31U)
#define CONV_SIZE               (SAMPLE_COUNT + FIR_TAP_COUNT - 1U)
#define LPF_CUT_OFF_HZ          (4000.0)

int main(void)
{
    /* Local variables */
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double coefficients[FIR_TAP_COUNT];
    double window[FIR_TAP_COUNT];
    double windowed[FIR_TAP_COUNT];
    double normalized[FIR_TAP_COUNT];
    double samples[DFT_SIZE];
    bin_t bins[DFT_SIZE];
    double samplesConvoluted[CONV_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t ampFreqChar[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    complex_t shiftedAmpFreqChar[FIR_TAP_COUNT];

    /* Print demo settings */
    ConfigSettingsPrint(FREQ_SAMPLE_HZ, SAMPLE_COUNT, ZERO_PADDING_COUNT, DFT_SIZE);

    /* Create signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 1.0, 0.0);

    /* Low pass filter and window */
    FIR_LowPassGenerate(coefficients, FIR_TAP_COUNT, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    WindowGenerate(WINDOW_HANN, window, FIR_TAP_COUNT);
    WindowApply(coefficients, window, windowed, FIR_TAP_COUNT);
    FIR_Normalize(windowed, normalized, FIR_TAP_COUNT, 1);

    /* Generate samples and save into file */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveDat("input.dat", samples, DFT_SIZE);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);

    /* Calculate DFT before FIR and save spectrum into file */
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_before_fir.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply convolution */
    Convolution(samples, samplesConvoluted, normalized, SAMPLE_COUNT, FIR_TAP_COUNT);

    /* Calculate DFT after FIR and save spectrum into file */
    DFT_Calculate(samplesConvoluted, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_after_fir.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Create FIR amplitude frequency characteristics */
    DFT_GenerateBins(bins, FIR_TAP_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(normalized, ampFreqChar, FIR_TAP_COUNT);
    DFT_ShiftSpectrum(ampFreqChar, shiftedAmpFreqChar, FIR_TAP_COUNT);
    SaveSpectrumDat("amp_freq_fir.dat", bins, shiftedAmpFreqChar, DFT_CalculateRawMagnitude, FIR_TAP_COUNT);

    return 0;
}
