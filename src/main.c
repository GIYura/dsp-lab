#include <stdio.h>

#include "config.h"
#include "signal.h"
#include "dft.h"
#include "fft.h"
#include "window.h"
#include "output.h"
#include "convolution.h"
#include "fir.h"

static harmonic_t signal[HARMONIC_COUNT];

#if DFT_ENABLE
static double dftSamples[DFT_SIZE];
#if FIR_ENABLE
static double dftSamplesConvoluted[CONV_SIZE];
#endif
static bin_t dftBins[DFT_SIZE];
#if WINDOW_ENABLE == 0
static complex_t dftSpectrumRaw[DFT_SIZE];
#endif
#endif

#if FFT_ENABLE
static fft_stage1_t fftStage1;
static fft_stage2_t fftStage2;
static double fftSamples[FFT_SIZE];
static bin_t fftBins[FFT_SIZE];
static complex_t fftSpectrumRaw[FFT_SIZE];
#endif

#if WINDOW_ENABLE
static double window[SAMPLE_COUNT];
static double dftSamplesWeighted[DFT_SIZE];
static complex_t dftSpectrumWeighted[DFT_SIZE];
#endif

#if FIR_ENABLE
static double firCoeff[FIR_TAP_COUNT];
static double firCoeffWindowed[FIR_TAP_COUNT];
static double firCoeffNormalized[FIR_TAP_COUNT];
#endif

#if DFT_ENABLE && FFT_ENABLE
#error "Only one algorithm can be enabled: DFT_ENABLE or FFT_ENABLE."
#endif

int main(void)
{
#if 0
    /* Create LPF */
    FIR_LowPassGenerate(firCoeff, FIR_TAP_COUNT, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    WindowGenerate(WINDOW_HANN, window, FIR_TAP_COUNT);
    WindowApply(firCoeff, window, firCoeffWindowed, FIR_TAP_COUNT);
    FIR_Normalize(firCoeffWindowed, firCoeffNormalized, FIR_TAP_COUNT);

    //SaveFirCoeffDat(firCoeff, FIR_TAP_COUNT);
    SaveDat("fir_coeff.dat", firCoeff, FIR_TAP_COUNT);
    SaveFirCoeffNormalizedDat(firCoeffNormalized, FIR_TAP_COUNT);
    SaveFirCoeffWindowedDat(firCoeffWindowed, FIR_TAP_COUNT);

    /* Create signal */
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 1.0, 0.0);

    SignalPrintConfig(signal, HARMONIC_COUNT);
    SignalGenerateSamples(signal, HARMONIC_COUNT, dftSamples, SAMPLE_COUNT);
    DFT_GenerateBins(dftBins, DFT_SIZE);

#if FIR_ENABLE
    Convolution(dftSamples, dftSamplesConvoluted, firCoeffNormalized, SAMPLE_COUNT, FIR_TAP_COUNT);
    DFT_Calculate(dftSamplesConvoluted, dftSpectrumRaw, DFT_SIZE);
#else
    DFT_Calculate(dftSamples, dftSpectrumRaw, DFT_SIZE);
#endif

    SaveInputDat(dftSamples, DFT_SIZE);
    SaveSpectrumDat(dftBins, dftSpectrumRaw, DFT_SIZE);
#endif

#if 1
    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 1.0, 0.0);

    ConfigSettingsPrint();
    SignalPrintConfig(signal, HARMONIC_COUNT);

#if DFT_ENABLE
    SignalGenerateSamples(signal, HARMONIC_COUNT, dftSamples, SAMPLE_COUNT);

#if WINDOW_ENABLE
    WindowGenerate(WINDOW_HANN, window, SAMPLE_COUNT);
    WindowApply(dftSamples, window, dftSamplesWeighted, SAMPLE_COUNT);
    SignalZeroPadding(dftSamplesWeighted, SAMPLE_COUNT, ZERO_PADDING_COUNT);
#else
    SignalZeroPadding(dftSamples, SAMPLE_COUNT, ZERO_PADDING_COUNT);
#endif

    DFT_GenerateBins(dftBins, DFT_SIZE);

#if WINDOW_ENABLE
    DFT_Calculate(dftSamplesWeighted, dftSpectrumWeighted, DFT_SIZE);
    DFT_Print(dftBins, dftSpectrumWeighted, DFT_SIZE);
#else
    DFT_Calculate(dftSamples, dftSpectrumRaw, DFT_SIZE);
    DFT_Print(dftBins, dftSpectrumRaw, DFT_SIZE);
#endif

    SignalPrintSamples(dftSamples, DFT_SIZE);

#if WINDOW_ENABLE
    SaveInputDat(dftSamples, DFT_SIZE);
    SaveSpectrumDat(dftBins, dftSpectrumWeighted, DFT_SIZE);
    SaveWindowDat(window, SAMPLE_COUNT);
    SaveWindowedSignalDat(dftSamplesWeighted, SAMPLE_COUNT);
#else
    SaveInputDat(dftSamples, DFT_SIZE);
    SaveSpectrumDat(dftBins, dftSpectrumRaw, DFT_SIZE);
#endif
#endif /* DFT_ENABLE */

#if FFT_ENABLE
    SignalGenerateSamples(signal, HARMONIC_COUNT, fftSamples, SAMPLE_COUNT);
    SignalZeroPadding(fftSamples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    FFT_GenerateBins(fftBins, FFT_SIZE);
    FFT_Stage1(fftSamples, &fftStage1);
    FFT_PrintStage1(&fftStage1);
    FFT_Stage2(&fftStage1, &fftStage2);
    FFT_PrintStage2(&fftStage2);
    FFT_Stage3(&fftStage2, fftSpectrumRaw);

    FFT_Print(fftBins, fftSpectrumRaw, FFT_SIZE);
    SaveInputDat(fftSamples, FFT_SIZE);
    SaveSpectrumDat(fftBins, fftSpectrumRaw, FFT_SIZE);
#endif /* FFT_ENABLE */
#endif
    return 0;
}
