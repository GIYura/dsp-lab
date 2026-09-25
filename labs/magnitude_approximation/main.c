/*
 * Magnitude approximation demo
 * */

#include <stdio.h>
#include <math.h>
#include <stdint.h>

#include "complex.h"

#define NUM     (5U)

typedef double (*fp_t)(complex_t value);

typedef struct
{
    char* name;
    fp_t callback;
} func_t;

static double MagnitudeExact(complex_t value)
{
    return sqrt(value.real * value.real + value.imag * value.imag);
}

static double MagnitudeApprox_Min2(complex_t value)
{
    double abs_i = fabs(value.real);
    double abs_q = fabs(value.imag);

    double max = fmax(abs_i, abs_q);
    double min = fmin(abs_i, abs_q);

    return max + (min / 2.0);
}

static double MagnitudeApprox_Min4(complex_t value)
{
    double abs_i = fabs(value.real);
    double abs_q = fabs(value.imag);

    double max = fmax(abs_i, abs_q);
    double min = fmin(abs_i, abs_q);

    return max + (min / 4.0);
}

static double MagnitudeApprox_Min3_8(complex_t value)
{
    double abs_i = fabs(value.real);
    double abs_q = fabs(value.imag);

    double max = fmax(abs_i, abs_q);
    double min = fmin(abs_i, abs_q);

    return max + ((3.0 * min) / 8.0);
}

static double MagnitudeApprox_7_Max_Min_2_8(complex_t value)
{
    double abs_i = fabs(value.real);
    double abs_q = fabs(value.imag);

    double max = fmax(abs_i, abs_q);
    double min = fmin(abs_i, abs_q);

    return (7.0 * (max + min / 2.0)) / 8;
}

static double MagnitudeApprox_15_Max_Min_2_16(complex_t value)
{
    double abs_i = fabs(value.real);
    double abs_q = fabs(value.imag);

    double max = fmax(abs_i, abs_q);
    double min = fmin(abs_i, abs_q);

    return (15.0 * (max + min / 2.0)) / 16;
}

static const func_t func[NUM] = {
        { "MAX+MIN/2", MagnitudeApprox_Min2 },
        { "MAX+MIN/4", MagnitudeApprox_Min4 },
        { "MAX+3*MIN/8", MagnitudeApprox_Min3_8 },
        { "7(MAX+MIN/2)/8", MagnitudeApprox_7_Max_Min_2_8 },
        { "15(MAX+MIN/2)/16", MagnitudeApprox_15_Max_Min_2_16 }
};

int main(void)
{
    double exact;
    double approx;
    double error;
    double errorMax = 0.0;
    complex_t value;

    for (uint32_t i = 0; i < NUM; i++)
    {
        printf("%s\n", func[i].name);
        printf("-------+-------+----------+------------+--------------|\n");
        printf("   I   |   Q   |   Exact  |   Approx   |   Error,%%    |\n");
        printf("-------+-------+----------+------------+--------------|\n");

        for (double q = 0.0; q <= 1.0; q += 0.01)
        {
            value.real = 1.0;
            value.imag = q;

            exact = MagnitudeExact(value);
            approx = (*func[i].callback)(value);
            error = (approx - exact) / exact * 100.0;
            if (fabs(error) > fabs(errorMax))
            {
                errorMax = error;
            }
            printf("%6.2f %6.2f %8.2f %10.2f %12.2f\n", value.real, value.imag, exact, approx, error);
        }
        printf("Max error=%f\n\n", errorMax);
        errorMax = 0.0;
    }

    return 0;
}
