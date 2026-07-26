#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#define WINDOW_ENABLE       (1)

#define DFT_ENABLE          (1)
#define FFT_ENABLE          (0)

#define FREQ_SAMPLE_HZ      (8000.0)
#define PI                  (3.14159265358979323846)
#define DEGREE_TO_RAD(x)    (((x) * PI) / 180.0)
#define RAD_TO_DEGREE(x)    (((x) * 180) / PI)
#define HARMONIC_COUNT      (3U)
#define SAMPLE_COUNT        (128U)
#define ZERO_PADDING_COUNT  (512U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define FFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)

/* DFT and FFT bin description */
typedef struct
{
    uint16_t number;
    double freqHz;
} bin_t;

/* Brief: Print application settings
* [in] - none
* [out] - none
* */
void ConfigSettingsPrint(void);

#endif /* CONFIG_H */
