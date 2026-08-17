#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "output.h"

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
        fprintf(fp,"%u %.6f %.12f\n", bins[i].number, (bins[i].freqHz * 0.001), callback(&spectrum[i]));
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
