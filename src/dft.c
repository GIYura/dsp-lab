#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "dft.h"

static void GenerateSinTemplate(uint16_t binNumber, double* const template, uint16_t count)
{
    double angle;
#if 0
    uint32_t degree;
    printf(" sin template\n");
    printf(" bin number=%d\n", binNumber);
#endif
    for (uint16_t i = 0; i < count; i++)
    {
        angle = 2.0 * PI * (double)binNumber * (double)i / (double)count;
        template[i] = sin(angle);
#if 0
        degree = RAD_TO_DEGREE(angle);
        printf("degree=%u\n", degree);
#endif
    }
}

static void GenerateCosTemplate(uint16_t binNumber, double* const template, uint16_t count)
{
    double angle;
#if 0
    uint32_t degree;
    printf(" cos template\n");
    printf(" bin number=%d\n", binNumber);
#endif
    for (uint16_t i = 0; i < count; i++)
    {
        angle = 2.0 * PI * (double)binNumber * (double)i / (double)count;
        template[i] = cos(angle);
#if 0
        degree = RAD_TO_DEGREE(angle);
        printf("degree=%u\n", degree);
#endif
    }
}

static double CompareTemplate(const double* const samples, const double* const template, uint16_t count)
{
    double result = 0.0;

    for (uint16_t i = 0; i < count; i++)
    {
        result += samples[i] * template[i];
    }

    return result;
}

void DFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    assert(samples != NULL);
    assert(spectrum != NULL);

    double sinTemplate[count];
    double cosTemplate[count];

    for (uint16_t i = 0; i < count; i++)
    {
        GenerateSinTemplate(i, sinTemplate, count);
        GenerateCosTemplate(i, cosTemplate, count);

        spectrum[i].imag = -CompareTemplate(samples, sinTemplate, count);
        spectrum[i].real = CompareTemplate(samples, cosTemplate, count);
    }
}

void DFT_GenerateBins(bin_t* const bins, uint16_t count)
{
    assert(bins != NULL);

    double binStep = FREQ_SAMPLE_HZ / (double)count;

    for (uint16_t i = 0; i < count; i++)
    {
        bins[i].number = i;
        bins[i].freqHz = (double)i * binStep;
    }
}

double DFT_CalculateRawMagnitude(const complex_t* const spectrum)
{
    assert(spectrum != NULL);

    return sqrt(spectrum->imag * spectrum->imag + spectrum->real * spectrum->real);
}

void DFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count)
{
    assert(bins != NULL);
    assert(spectrum != NULL);

    printf("DFT result:\n");
    printf(" bin | frequency, Hz | sin result | cos result | magnitude\n");
    printf("-----+---------------+------------+------------+-----------\n");

    for (uint16_t i = 0; i < count; i++)
    {
        printf(" %3u | %13.3f | %11.4f | %11.4f | %9.4f\n",
                bins[i].number,
                bins[i].freqHz,
                spectrum[i].imag,
                spectrum[i].real,
                DFT_CalculateRawMagnitude(&spectrum[i]));
    }
}
