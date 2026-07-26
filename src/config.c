#include <stdio.h>

#include "config.h"

void ConfigSettingsPrint(void)
{
    printf("--------------------------\n");
    printf("Application config\n");
    printf("--------------------------\n");
    printf("Settings:\n");
    printf("Fs = %.2f Hz\n", FREQ_SAMPLE_HZ);
    printf("Real samples = %u\n", SAMPLE_COUNT);
    printf("Zero padding = %u\n", ZERO_PADDING_COUNT);

#if DFT_ENABLE
    printf("DFT Bin step = %.3f Hz\n", FREQ_SAMPLE_HZ / (double)DFT_SIZE);
#endif
#if FFT_ENABLE
    printf("FFT Bin step = %.3f Hz\n\n", FREQ_SAMPLE_HZ / (double)FFT_SIZE);
#endif
}
