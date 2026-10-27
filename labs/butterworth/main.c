/*
 * Butterworth IIR 6-order
 * */

#include <stdio.h>

#include "sos.h"
#include "config.h"
#include "dft.h"
#include "save.h"

#define RESPONSE_COUNT          (1024)
#define FREQ_SAMPLE_HZ          (16000.0)

int main (void)
{
    sos_t sos;
    double impulse[RESPONSE_COUNT] = {0};
    double output[RESPONSE_COUNT] = {0};
    complex_t ampFreqChar[RESPONSE_COUNT];
    complex_t shiftedAmpFreqChar[RESPONSE_COUNT];
    bin_t responseBins[RESPONSE_COUNT];

    /* Create impulse response */
    impulse[0] = 1.0;

    /* Sos init */
    SosInit(&sos);

    /* add biquad sections to sos */
    if (!SosAddSection(&sos, 0.0017281882044323442, 0.0034563764088646884, 0.0017281882044323442, 1, -0.7439938352675736, 0.15131005454964727))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos));
        return 1;
    }

    if (!SosAddSection(&sos, 1, 2, 1, 1, -0.8394406674521644, 0.2990114095340083))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos));
        return 1;
    }

    if (!SosAddSection(&sos, 1, 2, 1, 1, -1.0792562377995951, 0.6701194272224298))
    {
        printf("Failed to add section [%d] to SOS\n", SosGetSectionCount(&sos));
        return 1;
    }

    /* Sos process */
    if (!SosProcess(&sos, impulse, output, RESPONSE_COUNT))
    {
        printf("Failed to process SOS; no active biquad section; section count=%u\n", SosGetSectionCount(&sos));
        return 2;
    }

    /* amp-freq response */
    DFT_GenerateBins(responseBins, RESPONSE_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(output, ampFreqChar, RESPONSE_COUNT);
    DFT_ShiftSpectrum(ampFreqChar, shiftedAmpFreqChar, RESPONSE_COUNT);
    SaveSpectrumDat("amp_freq_butterworth_impulse_response.dat", responseBins, shiftedAmpFreqChar, DFT_CalculateRawMagnitude, RESPONSE_COUNT);

    return 0;
}
