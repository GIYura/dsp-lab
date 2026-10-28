/*
 * Butterworth float vs double IIR 6-order
 * */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "sos.h"
#include "config.h"
#include "dft.h"
#include "save.h"

#define RESPONSE_COUNT          (1024)
#define FREQ_SAMPLE_HZ          (16000.0)

static void Compare(const double* const src1, const double* const src2, uint32_t size)
{
    assert(src1 != NULL);
    assert(src2 != NULL);

    double delta;

    for (uint32_t i = 0; i < size; i++)
    {
        delta = src1[i] - src2[i];
        printf("Delta[%u]=%.12e\n", i, delta);
    }
}

int main (void)
{
    sos_t sos_double;
    sos_t sos_float;

    double output_double[RESPONSE_COUNT] = {0};
    complex_t ampFreqChar_double[RESPONSE_COUNT];
    complex_t shiftedAmpFreqChar_double[RESPONSE_COUNT];
    bin_t responseBins_double[RESPONSE_COUNT];

    double output_float[RESPONSE_COUNT] = {0};
    complex_t ampFreqChar_float[RESPONSE_COUNT];
    complex_t shiftedAmpFreqChar_float[RESPONSE_COUNT];
    bin_t responseBins_float[RESPONSE_COUNT];

    double a0_double, a1_double, a2_double, b0_double, b1_double, b2_double;
    float a0_float, a1_float, a2_float, b0_float, b1_float, b2_float;

    double impulse[RESPONSE_COUNT] = {0};

/*
 * DOUBLE
 * */
    /* Create impulse response */
    impulse[0] = 1.0;

    /* Sos init */
    SosInit(&sos_double);

    /* Section #0 */
    a0_double = 1;
    a1_double = -0.7439938352675736;
    a2_double = 0.15131005454964727;
    b0_double = 0.0017281882044323442;
    b1_double = 0.0034563764088646884;
    b2_double = 0.0017281882044323442;

    /* add biquad sections to sos */
    if (!SosAddSection(&sos_double, b0_double, b1_double, b2_double, a0_double, a1_double, a2_double))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_double));
        return 1;
    }

    /* Section #1 */
    a0_double = 1;
    a1_double = -0.8394406674521644;
    a2_double = 0.2990114095340083;
    b0_double = 1;
    b1_double = 2;
    b2_double = 1;

    if (!SosAddSection(&sos_double, b0_double, b1_double, b2_double, a0_double, a1_double, a2_double))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_double));
        return 1;
    }

    /* Section #2 */
    a0_double = 1;
    a1_double = -1.0792562377995951;
    a2_double = 0.6701194272224298;
    b0_double = 1;
    b1_double = 2;
    b2_double = 1;

    if (!SosAddSection(&sos_double, b0_double, b1_double, b2_double, a0_double, a1_double, a2_double))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_double));
        return 1;
    }

    /* Sos process */
    if (!SosProcess(&sos_double, impulse, output_double, RESPONSE_COUNT))
    {
        printf("Failed to process SOS; no active biquad section; section count=%u\n", SosGetSectionCount(&sos_double));
        return 2;
    }

/*
 * FLOAT
 * */

    /* Sos init */
    SosInit(&sos_float);

    /* Section #0 */
    a0_float = 1;
    a1_float = -0.7439938352675736;
    a2_float = 0.15131005454964727;
    b0_float = 0.0017281882044323442;
    b1_float = 0.0034563764088646884;
    b2_float = 0.0017281882044323442;

    /* add biquad sections to sos */
    if (!SosAddSection(&sos_float, b0_float, b1_float, b2_float, a0_float, a1_float, a2_float))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_float));
        return 1;
    }

    /* Section #1 */
    a0_float = 1;
    a1_float = -0.8394406674521644;
    a2_float = 0.2990114095340083;
    b0_float = 1;
    b1_float = 2;
    b2_float = 1;

    if (!SosAddSection(&sos_float, b0_float, b1_float, b2_float, a0_float, a1_float, a2_float))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_float));
        return 1;
    }

    /* Section #2 */
    a0_float = 1;
    a1_float = -1.0792562377995951;
    a2_float = 0.6701194272224298;
    b0_float = 1;
    b1_float = 2;
    b2_float = 1;

    if (!SosAddSection(&sos_float, b0_float, b1_float, b2_float, a0_float, a1_float, a2_float))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos_float));
        return 1;
    }

    /* Sos process */
    if (!SosProcess(&sos_float, impulse, output_float, RESPONSE_COUNT))
    {
        printf("Failed to process SOS; no active biquad section; section count=%u\n", SosGetSectionCount(&sos_float));
        return 2;
    }

    /* amp-freq response (double) */
    DFT_GenerateBins(responseBins_double, RESPONSE_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(output_double, ampFreqChar_double, RESPONSE_COUNT);
    DFT_ShiftSpectrum(ampFreqChar_double, shiftedAmpFreqChar_double, RESPONSE_COUNT);
    SaveSpectrumDat("amp_freq_butterworth_impulse_response_double.dat", responseBins_double, shiftedAmpFreqChar_double, DFT_CalculateRawMagnitude, RESPONSE_COUNT);

    /* amp-freq response (float) */
    DFT_GenerateBins(responseBins_float, RESPONSE_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(output_float, ampFreqChar_float, RESPONSE_COUNT);
    DFT_ShiftSpectrum(ampFreqChar_float, shiftedAmpFreqChar_float, RESPONSE_COUNT);
    SaveSpectrumDat("amp_freq_butterworth_impulse_response_float.dat", responseBins_float, shiftedAmpFreqChar_float, DFT_CalculateRawMagnitude, RESPONSE_COUNT);

    Compare(output_double, output_float, RESPONSE_COUNT);

    return 0;
}
