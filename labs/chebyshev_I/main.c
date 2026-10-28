/*
 * Chebyshev_I IIR 4-order
 * */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "sos.h"
#include "config.h"
#include "dft.h"
#include "save.h"
#include "signal.h"

#define FREQ_1_HZ               (1000.0)
#define FREQ_2_HZ               (5000.0)

#define RESPONSE_COUNT          (1024)
#define FREQ_SAMPLE_HZ          (16000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define WARMUP_COUNT            (1024U)
#define TOTAL_COUNT             (WARMUP_COUNT + SAMPLE_COUNT)

static double CalculateGain(double freqHz, double freqSampleHz, const complex_t* const spectrumAfter, const complex_t* const spectrumBefore, uint32_t size)
{
    assert(spectrumAfter != NULL);
    assert(spectrumBefore != NULL);

    uint32_t freqIndex;
    double ampBeforeFilter;
    double ampAfterFilter;
    double gainDb;
    double binStep;

    binStep = freqSampleHz / size;
    freqIndex = freqHz / binStep;

    assert(freqIndex < size);

    ampBeforeFilter = DFT_CalculateRawMagnitude(&spectrumBefore[freqIndex]);
    ampAfterFilter = DFT_CalculateRawMagnitude(&spectrumAfter[freqIndex]);

    gainDb = 20.0 * log10(ampAfterFilter / ampBeforeFilter);

    return gainDb;
}

int main (void)
{
    sos_t sos;
    double impulse[RESPONSE_COUNT] = {0};
    double impulseOutput[RESPONSE_COUNT] = {0};
    complex_t spectrumResponse[RESPONSE_COUNT];
    complex_t shiftedSpectrumResponse[RESPONSE_COUNT];
    bin_t responseBins[RESPONSE_COUNT];

    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[TOTAL_COUNT] = {0};
    bin_t bins[DFT_SIZE];
    complex_t spectrumBeforeFilter[DFT_SIZE];
    complex_t spectrumAfterFilter[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];

    double warmupOutput[WARMUP_COUNT] = {0};
    double filteredSamples[SAMPLE_COUNT] = {0};

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, FREQ_1_HZ, 1.0, 0.0);
    SignalHarmonicAdd(signal, FREQ_2_HZ, 1.0, 0.0);

    /* Generate samples */
    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, TOTAL_COUNT, FREQ_SAMPLE_HZ);

    /* Calculate DFT */
    DFT_GenerateBins(bins, DFT_SIZE, FREQ_SAMPLE_HZ);
    DFT_Calculate(&samples[WARMUP_COUNT], spectrumBeforeFilter, DFT_SIZE);
    DFT_ShiftSpectrum(spectrumBeforeFilter, shiftedSpectrum, DFT_SIZE);

    /* Save into files for plot */
    SaveDat("time_domain_signal.dat", &samples[WARMUP_COUNT], DFT_SIZE);
    SaveSpectrumDat("spectrum_before_filter.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* Create impulse response */
    impulse[0] = 1.0;

    /* Sos init */
    SosInit(&sos);

    /* add biquad sections to sos */
    if (!SosAddSection(&sos, 0.00424123777940454, 0.00848247555880908, 0.00424123777940454, 1, -1.4349002533295665, 0.5793970270299895))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos));
        return 1;
    }

    if (!SosAddSection(&sos, 1, 2, 1, 1, -1.2931325194655292, 0.8200643738683813))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos));
        return 1;
    }

    /* Warm-up */
    if (!SosProcess(&sos, samples, warmupOutput, WARMUP_COUNT))
    {
        printf("Warm-up failed\n");
        return 2;
    }

    /* Sos process */
    if (!SosProcess(&sos, &samples[WARMUP_COUNT], filteredSamples, SAMPLE_COUNT))
    {
        printf("Failed to process SOS; no active biquad section; section count=%u\n", SosGetSectionCount(&sos));
        return 2;
    }

    /* Calculate DFT after IIR and save spectrum into file */
    DFT_Calculate(filteredSamples, spectrumAfterFilter, DFT_SIZE);
    DFT_ShiftSpectrum(spectrumAfterFilter, shiftedSpectrum, DFT_SIZE);
    SaveSpectrumDat("spectrum_after_filter.dat", bins, shiftedSpectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    /* amp-freq response */
    SosReset(&sos);
    if (!SosProcess(&sos, impulse, impulseOutput, RESPONSE_COUNT))
    {
        printf("Failed to process SOS after filter\n");
        return 2;
    }

    DFT_GenerateBins(responseBins, RESPONSE_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(impulseOutput, spectrumResponse, RESPONSE_COUNT);
    DFT_ShiftSpectrum(spectrumResponse, shiftedSpectrumResponse, RESPONSE_COUNT);
    SaveSpectrumDat("chebyshev_I_4_order_impulse_response.dat", responseBins, shiftedSpectrumResponse, DFT_CalculateRawMagnitude, RESPONSE_COUNT);

    printf("Filter gain(%.2f)=%f dB\n", FREQ_1_HZ, CalculateGain(FREQ_1_HZ, FREQ_SAMPLE_HZ, spectrumAfterFilter, spectrumBeforeFilter, DFT_SIZE));
    printf("Filter gain(%.2f)=%f dB\n", FREQ_2_HZ, CalculateGain(FREQ_2_HZ, FREQ_SAMPLE_HZ, spectrumAfterFilter, spectrumBeforeFilter, DFT_SIZE));

    return 0;
}
