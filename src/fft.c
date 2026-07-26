#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "fft.h"

static complex_t CalculateRotateMultiplier(uint16_t multiplierIndex, uint16_t butterflySize)
{
    complex_t result;
    double angle;

    angle = 2.0 * PI * (double)multiplierIndex / (double)butterflySize;

    result.real = cos(angle);
    result.imag = -sin(angle);

    return result;
}

void FFT_Stage1(const double* const samples, fft_stage1_t* const stage)
{
    assert(samples != NULL);
    assert(stage != NULL);

    stage->sum_0_4 = samples[0] + samples[4];
    stage->diff_0_4 = samples[0] - samples[4];

    stage->sum_1_5 = samples[1] + samples[5];
    stage->diff_1_5 = samples[1] - samples[5];

    stage->sum_2_6 = samples[2] + samples[6];
    stage->diff_2_6 = samples[2] - samples[6];

    stage->sum_3_7 = samples[3] + samples[7];
    stage->diff_3_7 = samples[3] - samples[7];
}

void FFT_Stage2(const fft_stage1_t* const stage1, fft_stage2_t* const stage2)
{
    complex_t upper;
    complex_t lower;
    complex_t lowerRotated;
    complex_t w;

    assert(stage1 != NULL);
    assert(stage2 != NULL);

    /* A0 = sum_0_4 + sum_2_6 * W4^0 */
    w = CalculateRotateMultiplier(0, 4);
    upper.real = stage1->sum_0_4;
    upper.imag = 0.0;
    lower.real = stage1->sum_2_6;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->a0 = ComplexAdd(upper, lowerRotated);

    /* A1 = diff_0_4 + diff_2_6 * W4^1 */
    w = CalculateRotateMultiplier(1, 4);
    upper.real = stage1->diff_0_4;
    upper.imag = 0.0;
    lower.real = stage1->diff_2_6;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->a1 = ComplexAdd(upper, lowerRotated);

    /* A2 = sum_0_4 + sum_2_6 * W4^2 */
    w = CalculateRotateMultiplier(2, 4);
    upper.real = stage1->sum_0_4;
    upper.imag = 0.0;
    lower.real = stage1->sum_2_6;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->a2 = ComplexAdd(upper, lowerRotated);

    /* A3 = diff_0_4 + diff_2_6 * W4^3 */
    w = CalculateRotateMultiplier(3, 4);
    upper.real = stage1->diff_0_4;
    upper.imag = 0.0;
    lower.real = stage1->diff_2_6;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->a3 = ComplexAdd(upper, lowerRotated);

    /* B0 = sum_1_5 + sum_3_7 * W4^0 */
    w = CalculateRotateMultiplier(0, 4);
    upper.real = stage1->sum_1_5;
    upper.imag = 0.0;
    lower.real = stage1->sum_3_7;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->b0 = ComplexAdd(upper, lowerRotated);

    /* B1 = diff_1_5 + diff_3_7 * W4^1 */
    w = CalculateRotateMultiplier(1, 4);
    upper.real = stage1->diff_1_5;
    upper.imag = 0.0;
    lower.real = stage1->diff_3_7;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->b1 = ComplexAdd(upper, lowerRotated);

    /* B2 = sum_1_5 + sum_3_7 * W4^2 */
    w = CalculateRotateMultiplier(2, 4);
    upper.real = stage1->sum_1_5;
    upper.imag = 0.0;
    lower.real = stage1->sum_3_7;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->b2 = ComplexAdd(upper, lowerRotated);

    /* B3 = diff_1_5 + diff_3_7 * W4^3 */
    w = CalculateRotateMultiplier(3, 4);
    upper.real = stage1->diff_1_5;
    upper.imag = 0.0;
    lower.real = stage1->diff_3_7;
    lower.imag = 0.0;
    lowerRotated = ComplexMultiply(lower, w);
    stage2->b3 = ComplexAdd(upper, lowerRotated);
}

void FFT_Stage3(const fft_stage2_t* const stage2, complex_t* const spectrum)
{
    complex_t lowerRotated;
    complex_t w;

    assert(stage2 != NULL);
    assert(spectrum != NULL);

    /* X0 = A0 + B0 * W8^0 */
    w = CalculateRotateMultiplier(0, 8);
    lowerRotated = ComplexMultiply(stage2->b0, w);
    spectrum[0] = ComplexAdd(stage2->a0, lowerRotated);

    /* X1 = A1 + B1 * W8^1 */
    w = CalculateRotateMultiplier(1, 8);
    lowerRotated = ComplexMultiply(stage2->b1, w);
    spectrum[1] = ComplexAdd(stage2->a1, lowerRotated);

    /* X2 = A2 + B2 * W8^2 */
    w = CalculateRotateMultiplier(2, 8);
    lowerRotated = ComplexMultiply(stage2->b2, w);
    spectrum[2] = ComplexAdd(stage2->a2, lowerRotated);

    /* X3 = A3 + B3 * W8^3 */
    w = CalculateRotateMultiplier(3, 8);
    lowerRotated = ComplexMultiply(stage2->b3, w);
    spectrum[3] = ComplexAdd(stage2->a3, lowerRotated);

    /* X4 = A0 + B0 * W8^4 */
    w = CalculateRotateMultiplier(4, 8);
    lowerRotated = ComplexMultiply(stage2->b0, w);
    spectrum[4] = ComplexAdd(stage2->a0, lowerRotated);

    /* X5 = A1 + B1 * W8^5 */
    w = CalculateRotateMultiplier(5, 8);
    lowerRotated = ComplexMultiply(stage2->b1, w);
    spectrum[5] = ComplexAdd(stage2->a1, lowerRotated);

    /* X6 = A2 + B2 * W8^6 */
    w = CalculateRotateMultiplier(6, 8);
    lowerRotated = ComplexMultiply(stage2->b2, w);
    spectrum[6] = ComplexAdd(stage2->a2, lowerRotated);

    /* X7 = A3 + B3 * W8^7 */
    w = CalculateRotateMultiplier(7, 8);
    lowerRotated = ComplexMultiply(stage2->b3, w);
    spectrum[7] = ComplexAdd(stage2->a3, lowerRotated);
}

void FFT_Calculate(const double* const samples, complex_t* const spectrum)
{
    fft_stage1_t stage1;
    fft_stage2_t stage2;

    assert(samples != NULL);
    assert(spectrum != NULL);

    FFT_Stage1(samples, &stage1);
    FFT_Stage2(&stage1, &stage2);
    FFT_Stage3(&stage2, spectrum);
}

void FFT_PrintStage1(const fft_stage1_t* const stage)
{
    assert(stage != NULL);

    printf("FFT stage 1:\n");
    printf(" sum_0_4  = %10.4f\n", stage->sum_0_4);
    printf(" sum_1_5  = %10.4f\n", stage->sum_1_5);
    printf(" sum_2_6  = %10.4f\n", stage->sum_2_6);
    printf(" sum_3_7  = %10.4f\n", stage->sum_3_7);
    printf(" diff_0_4 = %10.4f\n", stage->diff_0_4);
    printf(" diff_1_5 = %10.4f\n", stage->diff_1_5);
    printf(" diff_2_6 = %10.4f\n", stage->diff_2_6);
    printf(" diff_3_7 = %10.4f\n\n", stage->diff_3_7);
}

void FFT_PrintStage2(const fft_stage2_t* const stage)
{
    assert(stage != NULL);

    printf("FFT stage 2:\n");
    printf(" A0 = %10.4f %+.4fj\n", stage->a0.real, stage->a0.imag);
    printf(" A1 = %10.4f %+.4fj\n", stage->a1.real, stage->a1.imag);
    printf(" A2 = %10.4f %+.4fj\n", stage->a2.real, stage->a2.imag);
    printf(" A3 = %10.4f %+.4fj\n", stage->a3.real, stage->a3.imag);
    printf(" B0 = %10.4f %+.4fj\n", stage->b0.real, stage->b0.imag);
    printf(" B1 = %10.4f %+.4fj\n", stage->b1.real, stage->b1.imag);
    printf(" B2 = %10.4f %+.4fj\n", stage->b2.real, stage->b2.imag);
    printf(" B3 = %10.4f %+.4fj\n\n", stage->b3.real, stage->b3.imag);
}

void FFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count)
{
    assert(spectrum != NULL);
    assert(bins != NULL);

    printf("FFT result:\n");
    printf(" bin | frequency, Hz | sin result | cos result | magnitude\n");
    printf("-----+---------------+------------+------------+-----------\n");

    for (uint16_t i = 0; i < count; i++)
    {
        printf(" %3u | %13.4f | %10.4f | %10.4f | %9.4f\n",
                bins[i].number,
                bins[i].freqHz,
                spectrum[i].imag,
                spectrum[i].real,
                FFT_CalculateRawMagnitude(&spectrum[i]));
    }
}

double FFT_CalculateRawMagnitude(const complex_t* const spectrum)
{
    assert(spectrum != NULL);

    return sqrt(spectrum->imag * spectrum->imag + spectrum->real * spectrum->real);
}

void FFT_GenerateBins(bin_t* const bins, uint16_t count)
{
    assert(bins != NULL);
    assert(count > 0U);

    double binStep = FREQ_SAMPLE_HZ / (double)count;

    for (uint16_t i = 0U; i < count; i++)
    {
        bins[i].number = i;
        bins[i].freqHz = (double)i * binStep;
    }
}

#if 0
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "fft.h"

static int IsPowerOfTwo(uint16_t value)
{
    return value != 0U && (value & (value - 1U)) == 0U;
}

static uint8_t CalculateIndexBitCount(uint16_t count)
{
    uint8_t bitCount = 0U;

    while (count > 1U)
    {
        count >>= 1U;
        bitCount++;
    }

    return bitCount;
}

static uint16_t ReverseIndexBits(uint16_t index, uint8_t bitCount)
{
    uint16_t reversed = 0U;

    for (uint8_t i = 0U; i < bitCount; i++)
    {
        reversed <<= 1U;
        reversed |= index & 1U;
        index >>= 1U;
    }

    return reversed;
}

static complex_t CalculateRotateMultiplier(uint16_t multiplierIndex, uint16_t butterflySize)
{
    complex_t result;
    double angle;

    angle = 2.0 * PI * (double)multiplierIndex / (double)butterflySize;

    result.real = cos(angle);
    result.imag = -sin(angle);

    return result;
}

static void ArrangeSamples(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    uint8_t bitCount;
    uint16_t reversedIndex;

    bitCount = CalculateIndexBitCount(count);

    for (uint16_t i = 0U; i < count; i++)
    {
        reversedIndex = ReverseIndexBits(i, bitCount);
        spectrum[i].real = samples[reversedIndex];
        spectrum[i].imag = 0.0;
    }
}

static void CalculateStage(complex_t* const spectrum, uint16_t count, uint8_t stageNumber)
{
    uint16_t butterflySize;
    uint16_t butterflyHalfSize;
    uint16_t upperIndex;
    uint16_t lowerIndex;
    complex_t upper;
    complex_t lower;
    complex_t w;
    complex_t lowerRotated;

    butterflySize = (uint16_t)(1U << stageNumber);
    butterflyHalfSize = butterflySize / 2U;

    assert(butterflySize <= count);

    for (uint16_t groupStart = 0U; groupStart < count; groupStart += butterflySize)
    {
        for (uint16_t multiplierIndex = 0U; multiplierIndex < butterflyHalfSize; multiplierIndex++)
        {
            upperIndex = groupStart + multiplierIndex;
            lowerIndex = upperIndex + butterflyHalfSize;

            upper = spectrum[upperIndex];
            lower = spectrum[lowerIndex];

            w = CalculateRotateMultiplier(multiplierIndex, butterflySize);
            lowerRotated = ComplexMultiply(lower, w);

            spectrum[upperIndex] = ComplexAdd(upper, lowerRotated);
            spectrum[lowerIndex] = ComplexSubtract(upper, lowerRotated);
        }
    }
}

void FFT_Stage1(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    assert(samples != NULL);
    assert(spectrum != NULL);
    assert(IsPowerOfTwo(count));
    assert(count >= 2U);

    ArrangeSamples(samples, spectrum, count);
    CalculateStage(spectrum, count, 1U);
}

void FFT_Stage2(complex_t* const spectrum, uint16_t count)
{
    assert(spectrum != NULL);
    assert(IsPowerOfTwo(count));
    assert(count >= 4U);

    CalculateStage(spectrum, count, 2U);
}

void FFT_Stage3(complex_t* const spectrum, uint16_t count)
{
    assert(spectrum != NULL);
    assert(IsPowerOfTwo(count));
    assert(count >= 8U);

    CalculateStage(spectrum, count, 3U);
}

void FFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count)
{
    uint8_t stageCount;

    assert(samples != NULL);
    assert(spectrum != NULL);
    assert(IsPowerOfTwo(count));
    assert(count >= 2U);

    stageCount = CalculateIndexBitCount(count);

    FFT_Stage1(samples, spectrum, count);

    if (stageCount >= 2U)
    {
        FFT_Stage2(spectrum, count);
    }

    if (stageCount >= 3U)
    {
        FFT_Stage3(spectrum, count);
    }

    for (uint8_t stageNumber = 4U; stageNumber <= stageCount; stageNumber++)
    {
        CalculateStage(spectrum, count, stageNumber);
    }
}

void FFT_GenerateBins(fft_bin_t* const bins, uint16_t count)
{
    assert(bins != NULL);
    assert(count > 0U);

    double binStep = FREQ_SAMPLE_HZ / (double)count;

    for (uint16_t i = 0U; i < count; i++)
    {
        bins[i].number = i;
        bins[i].freqHz = (double)i * binStep;
    }
}

double FFT_CalculateRawMagnitude(const complex_t* const spectrum)
{
    assert(spectrum != NULL);

    return sqrt(spectrum->imag * spectrum->imag + spectrum->real * spectrum->real);
}

void FFT_Print(const fft_bin_t* const bins, const complex_t* const spectrum, uint16_t count)
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
#endif
