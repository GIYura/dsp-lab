#include <assert.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

#include "signal.h"
#include "config.h"

bool SignalHarmonicAdd(harmonic_t* const harmonic, double freqHz, double amp, double phaseDeg)
{
    assert(harmonic != NULL);

    bool result = false;

        for (uint8_t i = 0; i < HARMONIC_COUNT; i++)
        {
            if (harmonic[i].freqHz == 0 && harmonic[i].amp == 0 && harmonic[i].phaseDeg == 0)
            {
                harmonic[i].freqHz = freqHz;
                harmonic[i].amp = amp;
                harmonic[i].phaseDeg = phaseDeg;

                result = true;

                break;
            }
        }

        return result;
}

void SignalGenerateSamples(const harmonic_t* const harmonic, uint8_t harmCount, double* samples, uint16_t sampleCount)
{
    assert(harmonic != NULL);
    assert(samples != NULL);

    double sec;
    double sample;
    double angle;
    double component;

    for (uint16_t i = 0; i < sampleCount; i++)
    {
        sec = (double)i / FREQ_SAMPLE_HZ;
        sample = 0.0;

        for (uint8_t j = 0; j < harmCount; j++)
        {
            angle = 2.0 * PI * harmonic[j].freqHz * sec + DEGREE_TO_RAD(harmonic[j].phaseDeg);
            component = harmonic[j].amp * sin(angle);
            sample += component;
        }

        samples[i] = sample;
    }
}

void SignalZeroPadding(double* samples, uint16_t sampleCount, uint16_t zeroCount)
{
    assert(samples != NULL);

    for (uint16_t i = 0; i < zeroCount; i++)
    {
        samples[sampleCount + i] = 0;
    }
}

void SignalPrintSamples(const double* const samples, uint16_t count)
{
    assert(samples != NULL);

    double time_ms = 0.0;

    printf("Samples:\n");
    printf(" n | time, ms | x[n]\n");
    printf("---+----------+-----------\n");

    for (uint16_t i = 0; i < count; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        printf("%2u | %8.3f | %9.4f\n", i, time_ms, samples[i]);
    }

    printf("\n");
}

void SignalPrintConfig(const harmonic_t* const harmonic, uint16_t count)
{
    assert(harmonic != NULL);

    printf("Harmonics:\n");
    printf(" idx | frequency, Hz | amplitude | phase, deg\n");
    printf("-----+---------------+-----------+-----------\n");

    for (uint16_t i = 0; i < count; i++)
    {
        if (harmonic[i].amp != 0.0)
        {
            printf(" %3u | %13.3f | %9.3f | %10.3f\n", i, harmonic[i].freqHz, harmonic[i].amp, harmonic[i].phaseDeg);
        }
    }
    printf("\n");
}

