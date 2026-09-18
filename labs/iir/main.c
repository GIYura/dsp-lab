/*
 * IIR single-pole demo
 * */

#include "config.h"
#include "iir.h"
#include "save.h"
#include "signal.h"
#include "dft.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (16000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define LPF_CUT_OFF_HZ          (3000.0)

int main(void)
{
    iir_t filter;
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE];
    double output[DFT_SIZE];
    double output_2[DFT_SIZE];
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];

    double impulse[RESPONSE_SIZE] = {0};
    double response[RESPONSE_SIZE] = {0};
    double response_2[RESPONSE_SIZE] = {0};
    complex_t ampFreqChar[RESPONSE_SIZE];
    complex_t shiftedAmpFreqChar[RESPONSE_SIZE];
    bin_t responseBins[RESPONSE_SIZE];

    impulse[0] = 1.0;

    /* Generate LPF */
    IIR_LowPassGenerate(&filter, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    IIR_Print(&filter);

    /* Create signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 1.0, 0.0);

    /* Generate samples and save into file */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveDat("input.dat", samples, DFT_SIZE);

    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);

    /* Calculate DFT before IIR and save spectrum into file */
    DFT_Calculate(samples, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_before_iir.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Apply filter */
    IIR_Calculate(&filter, samples, output, SAMPLE_COUNT);
    IIR_Calculate(&filter, output, output_2, SAMPLE_COUNT);

    /* Calculate DFT after IIR and save spectrum into file */
    DFT_Calculate(output_2, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_after_iir.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Calculate amplitude frequency characteristics */
    IIR_LowPassGenerate(&filter, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    DFT_GenerateBins(responseBins, RESPONSE_SIZE, FREQ_SAMPLE_HZ);
    IIR_Calculate(&filter, impulse, response, RESPONSE_SIZE);
    IIR_Calculate(&filter, response, response_2, RESPONSE_SIZE);
    DFT_Calculate(response_2, ampFreqChar, RESPONSE_SIZE);
    DFT_ShiftSpectrum(ampFreqChar, shiftedAmpFreqChar, RESPONSE_SIZE);
    SaveSpectrumDat("amp_freq_iir.dat", responseBins, shiftedAmpFreqChar, DFT_CalculateRawMagnitude, RESPONSE_SIZE);

    return 0;
}
