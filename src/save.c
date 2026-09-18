#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "save.h"

void SaveSpectrumDat(const char* const fileName, const bin_t* bins, const complex_t* spectrum, fp_t cb, uint16_t count)
{
    assert(fileName != NULL);
    assert(bins != NULL);
    assert(spectrum != NULL);
    assert(cb != NULL);

    fp_t callback = cb;

    FILE *fp = fopen(fileName, "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        fprintf(fp, "%u %.6f %.12f\n", bins[i].number, bins[i].freqHz, callback(&spectrum[i]));
    }

    fclose(fp);
}

void SaveDat(const char* const fileName, const double* const in, uint32_t count)
{
    assert(fileName != NULL);
    assert(in != NULL);

    FILE *fp = fopen(fileName, "w");
    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        fprintf(fp, "%.6f\n", in[i]);
    }

    fclose(fp);
}

void SaveIQDat(const char* const fileName, const complex_t* const in, uint32_t count)
{
    assert(fileName != NULL);
    assert(in != NULL);

    FILE *fp = fopen(fileName, "w");
    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count - 1; i++)
    {
        fprintf(fp, "%.6f %.6f %.6f %.6f\n", in[i].real, in[i].imag, in[i + 1].real - in[i].real, in[i + 1].imag - in[i].imag);
    }

    fclose(fp);
}

void SaveTimeDat(const char *fileName, const double *in, uint32_t count, double sampleRateHz)
{
    assert(fileName != NULL);
    assert(in != NULL);
    assert(sampleRateHz > 0.0);

    FILE *fp = fopen(fileName, "w");

    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        double timeSec = (double)i / sampleRateHz;

        fprintf(fp, "%.9f %.6f\n", timeSec, in[i]);
    }

    fclose(fp);
}
