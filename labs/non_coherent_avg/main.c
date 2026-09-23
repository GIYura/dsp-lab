/*
 * Non-coherent averaging demo
 * */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "save.h"
#include "signal.h"
#include "noise.h"
#include "stats.h"
#include "dft.h"

#define FREQ_SAMPLE_HZ          (8000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)

int main(int argc, char* argv[])
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    double noise[SAMPLE_COUNT] = {0};
    double noisy[SAMPLE_COUNT] = {0};
    complex_t spectrum[DFT_SIZE];
    complex_t shiftedSpectrum[DFT_SIZE];
    double avePower[DFT_SIZE] = {0};
    double phaseRandom;
    uint32_t avgCount = 0;

    if (argc < 2)
    {
        printf("Invalid number of params\n");
        return 1;
    }

    avgCount = atoi(argv[1]);

    if (avgCount <= 0)
    {
        printf("Average count must be greater than zero\n");
        return 1;
    }

    for (uint32_t i = 0; i < avgCount; i++)
    {
        memset(signal, 0, sizeof(signal));

        phaseRandom = 360.0 * (double)rand() / (double)RAND_MAX;

        SignalHarmonicAdd(signal, 1000.0, 1.0, phaseRandom);
        SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT, FREQ_SAMPLE_HZ);

        NoiseGenerate(noise, SAMPLE_COUNT, 0.5);
        NoiseAdd(samples, noise, noisy, SAMPLE_COUNT);

        DFT_Calculate(noisy, spectrum, DFT_SIZE);
        DFT_ShiftSpectrum(spectrum, shiftedSpectrum, DFT_SIZE);

        for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
        {
            double power = shiftedSpectrum[i].real * shiftedSpectrum[i].real + shiftedSpectrum[i].imag * shiftedSpectrum[i].imag;
            avePower[i] += power;
        }
    }

    for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
    {
        avePower[i] /= avgCount;
    }

    if (avgCount == 1)
    {
        SaveDat("power_001.dat", avePower, SAMPLE_COUNT);
    }

    if (avgCount == 10)
    {
        SaveDat("power_010.dat", avePower, SAMPLE_COUNT);
    }

    if (avgCount == 100)
    {
        SaveDat("power_100.dat", avePower, SAMPLE_COUNT);
    }

    return 0;
}

