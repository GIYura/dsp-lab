/*
 * BIQUAD demo
 * */
#include "biquad.h"
#include "config.h"
#include "dft.h"
#include "save.h"

#define SECTION_COUNT           (3)
#define RESPONSE_COUNT          (1024)
#define FREQ_SAMPLE_HZ          (16000.0)

int main(void)
{
    biquad_t biqaud[SECTION_COUNT];
    double impulse[RESPONSE_COUNT] = {0};
    double buffer[SECTION_COUNT - 1][RESPONSE_COUNT];
    double output[RESPONSE_COUNT] = {0};
    complex_t ampFreqChar[RESPONSE_COUNT];
    complex_t shiftedAmpFreqChar[RESPONSE_COUNT];
    bin_t responseBins[RESPONSE_COUNT];

    for (uint32_t i = 0; i < SECTION_COUNT; i++)
    {
        BiquadInit(&biqaud[i]);
        BiquadReset(&biqaud[i]);
    }

    BiquadSetCoefficients(&biqaud[0], -0.7439938352675736, 0.15131005454964727, 0.0017281882044323442, 0.0034563764088646884, 0.0017281882044323442);
    BiquadSetCoefficients(&biqaud[1], -0.8394406674521644, 0.2990114095340083, 1.0, 2.0, 1.0);
    BiquadSetCoefficients(&biqaud[2], -1.0792562377995951, 0.6701194272224298, 1.0, 2.0, 1.0);

    impulse[0] = 1.0;

    BiquadProcess(&biqaud[0], impulse, buffer[0], RESPONSE_COUNT);
    BiquadProcess(&biqaud[1], buffer[0], buffer[1], RESPONSE_COUNT);
    BiquadProcess(&biqaud[2], buffer[1], output, RESPONSE_COUNT);

    DFT_GenerateBins(responseBins, RESPONSE_COUNT, FREQ_SAMPLE_HZ);
    DFT_Calculate(output, ampFreqChar, RESPONSE_COUNT);
    DFT_ShiftSpectrum(ampFreqChar, shiftedAmpFreqChar, RESPONSE_COUNT);
    SaveSpectrumDat("amp_freq_biqaud_impulse_response.dat", responseBins, shiftedAmpFreqChar, DFT_CalculateRawMagnitude, RESPONSE_COUNT);

    return 0;
}
