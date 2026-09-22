#include <assert.h>
#include <stddef.h>
#include <math.h>

#include "stats.h"

double StatsMean(const double* const samples, uint32_t count)
{
    assert(samples != NULL);
    assert(count > 0U);

    double sum = 0.0;

    for (uint32_t i = 0; i < count; i++)
    {
        sum += samples[i];
    }

    return sum / (double)count;
}

double StatsStandardDeviation(const double* const samples, uint32_t count)
{
    assert(samples != NULL);
    assert(count > 0U);

    double mean = StatsMean(samples, count);
    double sum = 0.0;
    double deviation;

    for (uint32_t i = 0; i < count; i++)
    {
        deviation = samples[i] - mean;
        sum += deviation * deviation;
    }

    return sqrt(sum / (double)count);
}
