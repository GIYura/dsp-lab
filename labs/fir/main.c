#include "config.h"
#include "fir.h"
#include "output.h"
#include "window.h"
#include "signal.h"
#include "dft.h"
#include "convolution.h"

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double coefficients[FIR_TAP_COUNT];
    double window[FIR_TAP_COUNT];
    double windowed[FIR_TAP_COUNT];
    double normalized[FIR_TAP_COUNT];
    double samples[DFT_SIZE];
    bin_t bins[DFT_SIZE];
    double samplesConvoluted[CONV_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t amp_freq[DFT_SIZE];

    /* Create signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 1.0, 0.0);

    /* Low pass filter and window */
    FIR_LowPassGenerate(coefficients, FIR_TAP_COUNT, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    WindowGenerate(WINDOW_HANN, window, FIR_TAP_COUNT);
    WindowApply(coefficients, window, windowed, FIR_TAP_COUNT);
    FIR_Normalize(windowed, normalized, FIR_TAP_COUNT);

    /* Generate samples and save into file */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    SaveDat("input.dat", samples, DFT_SIZE);

    DFT_GenerateBins(bins, DFT_SIZE);

    /* Calculate DFT before FIR and save spectrum into file */
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_before_fir.dat", bins, spectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Calculate DFT after FIR and save spectrum into file */
    Convolution(samples, samplesConvoluted, normalized, SAMPLE_COUNT, FIR_TAP_COUNT);
    DFT_Calculate(samplesConvoluted, spectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_after_fir.dat", bins, spectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Create FIR amplitude frequency characteristics */
    DFT_GenerateBins(bins, FIR_TAP_COUNT);
    DFT_Calculate(normalized, amp_freq, FIR_TAP_COUNT);
    SaveSpectrumDat("amp_freq_fir.dat", bins, amp_freq, DFT_CalculateRawMagnitude, (FIR_TAP_COUNT / 2));

    return 0;
}
