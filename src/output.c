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

    double timeMs = 0.0;

    FILE *fp = fopen("windowed.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        timeMs = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        fprintf(fp, "%2u %8.3f %9.4f\n" , i, timeMs, samples[i]);
    }

    fclose(fp);
}

void SaveInputDat(const double* samples, uint16_t count)
{
    assert(samples != NULL);

    double timeMs = 0.0;

    FILE *fp = fopen("input.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        timeMs = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        fprintf(fp, "%2u %8.3f %9.4f\n" , i, timeMs, samples[i]);
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

void SaveFirCoeffDat(const double* const coeff, uint32_t count)
{
    assert(coeff != NULL);

    FILE *fp = fopen("fir_coeff.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        fprintf(fp, "%.6f\n", coeff[i]);
    }

    fclose(fp);
}

void SaveFirCoeffWindowedDat(const double* const coeff, uint32_t count)
{
    assert(coeff != NULL);

    FILE *fp = fopen("fir_coeff_windowed.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        fprintf(fp," %.6f\n", coeff[i]);
    }

    fclose(fp);
}

void SaveFirCoeffNormalizedDat(const double* const coeff, uint32_t count)
{
    assert(coeff != NULL);

    FILE *fp = fopen("fir_coeff_normalized.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        fprintf(fp, "%.6f\n", coeff[i]);
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
