#include <assert.h>
#include <stddef.h>

#include "shift.h"

void SignalShift(const double* const in, const complex_t* const shift, complex_t* const out, uint32_t size)
{
    assert(in != NULL);
    assert(shift != NULL);
    assert(out != NULL);
    assert(size > 0);

    complex_t value;

    for (uint32_t i = 0; i < size; i++)
    {
        value.real = in[i];
        value.imag = 0.0;
        out[i] = ComplexMul(value, shift[i]);
    }
}

/*
 * NOTE: DSP 13.1.1
 * */
void ShiftOnHalfOfSampleFreq(const double* const src, double* const dst, uint32_t size)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(size > 0);

    for (uint32_t i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            dst[i] = src[i];
        }
        else
        {
            dst[i] = -src[i];
        }
    }
}

/*
 * NOTE: DSP 13.1.2
 * */
void ShiftMinusQuaterFs(const double* const src, complex_t* const dst, uint32_t size)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(size > 0);

    for (uint32_t i = 0; i < size; i++)
    {
        switch (i % 4U)
        {
        case 0: /* × (+1) */
            dst[i].real = src[i];
            dst[i].imag = 0.0;
            break;

        case 1: /* × (-j) */
            dst[i].real = 0.0;
            dst[i].imag = -src[i];
            break;

        case 2: /* × (-1) */
            dst[i].real = -src[i];
            dst[i].imag = 0.0;
            break;

        case 3: /* × (+j) */
            dst[i].real = 0.0;
            dst[i].imag = src[i];
            break;
        }
    }
}

/*
 * NOTE: DSP 13.1.2
 * */
void ShiftPlusQuaterFs(const double* const src, complex_t* const dst, uint32_t size)
{
    assert(src != NULL);
    assert(dst != NULL);
    assert(size > 0);

    for (uint32_t i = 0; i < size; i++)
    {
        switch (i % 4U)
        {
        case 0: /* × (+1) */
            dst[i].real = src[i];
            dst[i].imag = 0.0;
            break;

        case 1: /* × (+j) */
            dst[i].real = 0.0;
            dst[i].imag = src[i];
            break;

        case 2: /* × (-1) */
            dst[i].real = -src[i];
            dst[i].imag = 0.0;
            break;

        case 3: /* × (-j) */
            dst[i].real = 0.0;
            dst[i].imag = -src[i];
            break;
        }
    }
}

