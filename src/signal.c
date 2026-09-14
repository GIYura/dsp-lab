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
            //component = harmonic[j].amp * sin(angle);
            component = harmonic[j].amp * cos(angle);
            sample += component;
        }

        samples[i] = sample;
    }
}

void SignalGenerateIQSamples(const harmonic_t* harmonics, uint8_t harmCount, complex_t* const samples, uint16_t sampleCount)
{
    double sec;
    double angle;

    for (size_t i = 0; i < sampleCount; i++)
    {
        sec = (double)i / FREQ_SAMPLE_HZ;

        samples[i].real = 0.0;
        samples[i].imag = 0.0;

#if 1
        for (size_t j = 0; j < harmCount; j++)
        {
            angle = 2.0 * PI * harmonics[j].freqHz * sec + DEGREE_TO_RAD(harmonics[j].phaseDeg);

            samples[i].real += harmonics[j].amp * cos(angle);
            samples[i].imag += harmonics[j].amp * sin(angle);
        }
#endif
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

    printf(" Real Samples:\n");
    printf(" n | time, ms | x[n]      |\n");
    printf("---+----------+-----------|\n");

    for (uint16_t i = 0; i < count; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        printf("%2u | %8.3f | %9.4f |\n", i, time_ms, samples[i]);
    }

    printf("\n");
}

void SignalPrintIQSamples(const complex_t* const samples, uint16_t count)
{
    assert(samples != NULL);

    double time_ms = 0.0;

    printf(" IQ Samples:\n");
    printf(" n | time, ms | x[n] Re   | x[n] Im   |\n");
    printf("---+----------+-----------|-----------|\n");

    for (uint16_t i = 0; i < count; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        printf("%2u | %8.3f | %9.4f | %9.4f |\n", i, time_ms, samples[i].real, samples[i].imag);
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

