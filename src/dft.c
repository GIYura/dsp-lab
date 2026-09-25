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

static complex_t CompareTemplateComplex(const complex_t* const samples, const double* const cosTemplate, const double* const sinTemplate, uint16_t dftSize)
{
    complex_t result;

    result.imag = 0;
    result.real = 0;

    for (uint16_t i = 0; i < dftSize; i++)
    {
        result.real += samples[i].real * cosTemplate[i] + samples[i].imag * sinTemplate[i];
        result.imag += samples[i].imag * cosTemplate[i] - samples[i].real * sinTemplate[i];
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

void DFT_CalculateComplex(const complex_t* const samples, complex_t* const spectrum, uint16_t count)
{
    double sinTemplate[count];
    double cosTemplate[count];
    complex_t sample;

    for (size_t i = 0; i < count; i++)
    {
        GenerateSinTemplate(i, sinTemplate, count);
        GenerateCosTemplate(i, cosTemplate, count);

        sample = CompareTemplateComplex(samples, cosTemplate, sinTemplate, count);
        spectrum[i].real = sample.real;
        spectrum[i].imag = sample.imag;
    }
}

void DFT_GenerateBins(bin_t *const bins, uint16_t count, double sampleRateHz)
{
    assert(bins != NULL);
    assert(count > 0U);
    assert(sampleRateHz > 0.0);

    double binStep = sampleRateHz / (double)count;
    int32_t half = (int32_t)count / 2;

    for (uint16_t i = 0; i < count; i++)
    {
        int32_t shiftedIndex = (int32_t)i - half;

        bins[i].number = i;
        bins[i].freqHz = (double)shiftedIndex * binStep;
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
    printf(" bin | frequency, Hz | real result | imag result | magnitude\n");
    printf("-----+---------------+------------+------------+-----------\n");

    for (uint16_t i = 0; i < count; i++)
    {
        printf(" %3u | %13.3f | %11.4f | %11.4f | %9.4f\n",
                bins[i].number,
                bins[i].freqHz,
                spectrum[i].real,
                spectrum[i].imag,
                DFT_CalculateRawMagnitude(&spectrum[i]));
    }
}

void DFT_ShiftSpectrum(const complex_t *const input, complex_t *const output, uint16_t count)
{
    assert(input != NULL);
    assert(output != NULL);
    assert(count > 0);
    uint16_t shift = (count + 1U) / 2U;
    uint16_t src;

    for (uint16_t i = 0; i < count; i++)
    {
        src = (uint16_t)((i + shift) % count);
        output[i] = input[src];
    }
}

void DFT_SpectrumNormalize(complex_t* const spectrum, uint32_t count)
{
    assert(spectrum != NULL);
    assert(count > 0);

    double scale = 2.0 / (double)count;

    for (uint32_t i = 0; i < count; i++)
    {
        spectrum[i].real *= scale;
        spectrum[i].imag *= scale;
    }
}
