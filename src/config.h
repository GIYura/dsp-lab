#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#define PI                  (3.14159265358979323846)
#define DEGREE_TO_RAD(x)    (((x) * PI) / 180.0)
#define RAD_TO_DEGREE(x)    (((x) * 180) / PI)

#define FREQ_SAMPLE_HZ      (16000.0)
#define HARMONIC_COUNT      (3U)
#define SAMPLE_COUNT        (256U)
#define ZERO_PADDING_COUNT  (0U)

#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define FFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

#define FIR_TAP_COUNT       (31U)
#define CONV_SIZE           (SAMPLE_COUNT + FIR_TAP_COUNT - 1U)
#define LPF_CUT_OFF_HZ      (4000.0)

/* DFT and FFT bin description */
typedef struct
{
    uint16_t number;
    double freqHz;
} bin_t;

/* Brief: Print application settings
* [in] - freqSampleHz - sample frequency, Hz
* [in] - sampleCount - sample counter
* [in] - zeroPaddingCount - zero padding counter
* [in] - nfft - size of FFT/DFT
* [out] - none
* */
void ConfigSettingsPrint(double freqSampleHz, uint32_t sampleCount, uint32_t zeroPaddingCount, uint32_t nfft);

#endif /* CONFIG_H */
