#include <stdio.h>

#include "config.h"

void ConfigSettingsPrint(double freqSampleHz, uint32_t sampleCount, uint32_t zeroPaddingCount, uint32_t nfft)
{
    printf("--------------------------\n");
    printf("    Application config    \n");
    printf("--------------------------\n");
    printf("Fs = %.2f Hz\n", freqSampleHz);
    printf("Real samples = %u\n", sampleCount);
    printf("Zero padding = %u\n", zeroPaddingCount);
    printf("NFFT = %u\n", nfft);
    printf("--------------------------\n");
}
