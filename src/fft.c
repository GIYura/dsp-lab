#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "fft.h"

static int IsPowerOfTwo(uint16_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

static uint8_t CalculatePower_2(uint16_t count)
{
    uint8_t bitCount = 0;

    while (count > 1)
    {
        count >>= 1;
        bitCount++;
    }

    return bitCount;
}

static uint16_t ReverseIndexBits(uint16_t index, uint8_t bitCount)
{
    uint16_t reversed = 0;

    for (uint8_t i = 0; i < bitCount; i++)
    {
        reversed <<= 1;
        reversed |= index & 1;
        index >>= 1;
    }

    return reversed;
}

static complex_t CalculateTwiddleFactor(uint16_t index, uint16_t size)
{
    complex_t result;
    double angle;

    angle = 2.0 * PI * (double)index / (double)size;

    result.real = cos(angle);
    result.imag = -sin(angle);

    return result;
}

static void ArrangeSamples(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    uint8_t bitCount;
    uint16_t reversedIndex;

    bitCount = CalculatePower_2(count);

    for (uint16_t i = 0; i < count; i++)
    {
        reversedIndex = ReverseIndexBits(i, bitCount);
        spectrum[i].real = samples[reversedIndex];
        spectrum[i].imag = 0.0;
    }
}

static void CalculateStage(complex_t* const spectrum, uint16_t count, uint8_t stageNumber)
{
    uint16_t M;          /* size of local DFT */
    uint16_t M_half;     /* half of size of local DFT */
    uint16_t upperIndex;
    uint16_t lowerIndex;
    complex_t upper;
    complex_t lower;
    complex_t twiddleFactor;
    complex_t lowerRotated;
    uint16_t groupStart;        /* start of local DFT */
    uint16_t k;

    M = (uint16_t)(1 << stageNumber);
    M_half = M / 2;

    for (groupStart = 0; groupStart < count; groupStart += M)
    {
        for (k = 0; k < M_half; k++)
        {
            /* upperIndex = groupStart + k */
            upperIndex = groupStart + k;
            /* lowerIndex = groupStart + k + M/2 */
            lowerIndex = upperIndex + M_half;

            upper = spectrum[upperIndex];
            lower = spectrum[lowerIndex];

            twiddleFactor = CalculateTwiddleFactor(k, M);
            lowerRotated = ComplexMul(lower, twiddleFactor);

            spectrum[upperIndex] = ComplexAdd(upper, lowerRotated);
            spectrum[lowerIndex] = ComplexSub(upper, lowerRotated);
        }
    }
}

void FFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    uint8_t stageCount;

    assert(samples != NULL);
    assert(spectrum != NULL);
    assert(IsPowerOfTwo(count));
    assert(count >= 2U);

    stageCount = CalculatePower_2(count);

    ArrangeSamples(samples, spectrum, count);

    for (uint8_t stageNumber = 1; stageNumber <= stageCount; stageNumber++)
    {
        CalculateStage(spectrum, count, stageNumber);
    }
}

void FFT_GenerateBins(bin_t *const bins, uint16_t count, double sampleRateHz)
{
    assert(bins != NULL);
    assert(count > 0U);
    assert(sampleRateHz > 0.0);

    double binStep = sampleRateHz / (double)count;
    int32_t half = (int32_t)count / 2;

    for (uint16_t i = 0U; i < count; i++)
    {
        int32_t shiftedIndex = (int32_t)i - half;

        bins[i].number = i;
        bins[i].freqHz = (double)shiftedIndex * binStep;
    }
}

void FFT_ShiftSpectrum(const complex_t *const input, complex_t *const output, uint16_t count)
{
    assert(input != NULL);
    assert(output != NULL);
    assert(count > 0U);

    uint16_t shift = (count + 1U) / 2U;

    for (uint16_t i = 0U; i < count; i++)
    {
        uint16_t src = (uint16_t)((i + shift) % count);
        output[i] = input[src];
    }
}

double FFT_CalculateRawMagnitude(const complex_t* const spectrum)
{
    assert(spectrum != NULL);

    return sqrt(spectrum->imag * spectrum->imag + spectrum->real * spectrum->real);
}

void FFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count)
{
    assert(bins != NULL);
    assert(spectrum != NULL);

    printf("FFT result:\n");
    printf(" bin | frequency, Hz | real result | imag result | magnitude\n");
    printf("-----+---------------+-------------+-------------+-----------\n");

    for (uint16_t i = 0U; i < count; i++)
    {
        printf(" %3u | %13.3f | %11.4f | %11.4f | %9.4f\n",
                bins[i].number,
                bins[i].freqHz,
                spectrum[i].real,
                spectrum[i].imag,
                FFT_CalculateRawMagnitude(&spectrum[i]));
    }
}
