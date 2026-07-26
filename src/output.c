#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "output.h"
#include "config.h"

void SaveWindowDat(const double* samples, uint16_t count)
{
    assert(samples != NULL);

    FILE *fp = fopen("window.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        fprintf(fp, "%f\n", samples[i]);
    }

    fclose(fp);
}

void SaveWindowedSignalDat(const double* samples, uint16_t count)
{
    assert(samples != NULL);

    double time_ms = 0.0;

    FILE *fp = fopen("windowed.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        fprintf(fp, "%2u %8.3f %9.4f\n" , i, time_ms, samples[i]);
    }

    fclose(fp);
}

void SaveInputDat(const double* samples, uint16_t count)
{
    assert(samples != NULL);

    double time_ms = 0.0;

    FILE *fp = fopen("input.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        fprintf(fp, "%2u %8.3f %9.4f\n" , i, time_ms, samples[i]);
    }

    fclose(fp);
}

void SaveSpectrumDat(const bin_t* bins, const complex_t* spectrum, uint16_t count)
{
    assert(bins != NULL);
    assert(spectrum != NULL);

    FILE *fp = fopen("spectrum.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        fprintf(fp,"%u %.6f %.12f\n", bins[i].number, bins[i].freqHz, DFT_CalculateRawMagnitude(&spectrum[i]));
    }

    fclose(fp);
}
