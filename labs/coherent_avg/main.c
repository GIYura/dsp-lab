/*
 * Coherent averaging demo
 * */

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "save.h"
#include "signal.h"
#include "noise.h"
#include "stats.h"

#define FREQ_SAMPLE_HZ          (8000.0)
#define AVERAGE_COUNT           (256U)
#define AMPLITUDE               (1.0)

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double clean[SAMPLE_COUNT] = {0};
    double noise[SAMPLE_COUNT] = {0};
    double noisy[SAMPLE_COUNT] = {0};
    double averaged[SAMPLE_COUNT] = {0};
    double residualNoise[SAMPLE_COUNT] = {0};
    double sigmaNoise;
    double snrIn;
    double sigmaAveraged;
    double snrAve;

    double snrInDb;
    double snrAveDb;
    double snrRatio;
    double snrRatioDb;
    double expectedRatio;
    double expectedRatioDb;

    /* Add harmonics into signal */
    SignalHarmonicAdd(signal, 1000.0, AMPLITUDE, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 5000.0, 0.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, clean, SAMPLE_COUNT, FREQ_SAMPLE_HZ);
    SaveDat("clean.dat", clean, SAMPLE_COUNT);

    NoiseGenerate(noise, SAMPLE_COUNT, 0.5);
    NoiseAdd(clean, noise, noisy, SAMPLE_COUNT);
    SaveDat("noisy.dat", noisy, SAMPLE_COUNT);

    sigmaNoise = StatsStandardDeviation(noise, SAMPLE_COUNT);
    printf("Noise sigma = %f\n", sigmaNoise);

    snrIn = AMPLITUDE / sigmaNoise;
    printf("SNR in = %f\n", snrIn);

    for (uint32_t record = 0; record < AVERAGE_COUNT; record++)
    {
        NoiseGenerate(noise, SAMPLE_COUNT, 0.5);
        NoiseAdd(clean, noise, noisy, SAMPLE_COUNT);

        for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
        {
            averaged[i] += noisy[i];
        }
    }

    for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
    {
        averaged[i] /= AVERAGE_COUNT;
    }

    SaveDat("averaged.dat", averaged, SAMPLE_COUNT);

    for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
    {
        residualNoise[i] = averaged[i] - clean[i];
    }

    sigmaAveraged = StatsStandardDeviation(residualNoise, SAMPLE_COUNT);

    printf("Averaged noise sigma = %f\n", sigmaAveraged);

    snrAve = AMPLITUDE / sigmaAveraged;
    printf("SNR ave = %f\n", snrAve);

    printf("SNR ratio = %f\n", snrAve / snrIn);
    printf("SNR ratio = %f\n", sqrt(AVERAGE_COUNT));

    snrInDb = 20.0 * log10(snrIn);
    snrAveDb = 20.0 * log10(snrAve);

    snrRatio = snrAve / snrIn;
    snrRatioDb = 20.0 * log10(snrRatio);

    expectedRatio = sqrt((double)AVERAGE_COUNT);
    expectedRatioDb = 10.0 * log10((double)AVERAGE_COUNT);

    printf("SNR in          = %f (%f dB)\n", snrIn, snrInDb);
    printf("SNR ave         = %f (%f dB)\n", snrAve, snrAveDb);
    printf("SNR improvement = %f (%f dB)\n", snrRatio, snrRatioDb);
    printf("Expected        = %f (%f dB)\n", expectedRatio, expectedRatioDb);

    return 0;
}
