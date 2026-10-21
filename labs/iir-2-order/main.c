/*
 * IIR Second order demo
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
#define LPF_CUT_OFF_HZ          (2000.0)
#define RESPONSE_SIZE           (1024)
#define Z_TRANS_SIZE            (RESPONSE_SIZE / 2 + 1)

int main(void)
{
    IIR_Second_Order_t filter;
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[DFT_SIZE];
    double output[DFT_SIZE];
    bin_t bins[DFT_SIZE];
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];

    double impulse[RESPONSE_SIZE] = {0};
    double response[RESPONSE_SIZE] = {0};
    complex_t ampFreqChar[RESPONSE_SIZE];
    complex_t shiftedAmpFreqChar[RESPONSE_SIZE];
    bin_t responseBins[RESPONSE_SIZE];

    double outFreq[Z_TRANS_SIZE];
    double outMagnitude[Z_TRANS_SIZE];

    impulse[0] = 1.0;

    /* Generate LPF */
    IIR_SecondOrderInit(&filter);
    IIR_SecondOrderLowPassGenerate(&filter, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    IIR_SecondOrderPrint(&filter);

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
    IIR_SecondOrderCalculate(&filter, samples, output, SAMPLE_COUNT);

    /* Calculate DFT after IIR and save spectrum into file */
    DFT_Calculate(output, spectrum, DFT_SIZE);
    DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_after_iir.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Calculate amplitude frequency characteristics based on impulse response */
    IIR_SecondOrderInit(&filter);
    IIR_SecondOrderLowPassGenerate(&filter, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    DFT_GenerateBins(responseBins, RESPONSE_SIZE, FREQ_SAMPLE_HZ);
    IIR_SecondOrderCalculate(&filter, impulse, response, RESPONSE_SIZE);
    DFT_Calculate(response, ampFreqChar, RESPONSE_SIZE);
    DFT_ShiftSpectrum(ampFreqChar, shiftedAmpFreqChar, RESPONSE_SIZE);
    SaveSpectrumDat("amp_freq_iir_impulse_response.dat", responseBins, shiftedAmpFreqChar, DFT_CalculateRawMagnitude, RESPONSE_SIZE);

    /* Calculate amplitude frequency characteristics based on Z-transform */
    IIR_SecondOrderMagnitudeResponse(&filter, outFreq, outMagnitude, FREQ_SAMPLE_HZ, RESPONSE_SIZE);
    SaveXYDat("amp_freq_iir_z_trans.dat", outFreq, outMagnitude, Z_TRANS_SIZE);

    return 0;
}
