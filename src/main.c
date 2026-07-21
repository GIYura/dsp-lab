/*
 * */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"

#define FREQ_SAMPLE_HZ      (8000.0)
#define SAMPLE_COUNT        (128U)
#define ZERO_PADDING_COUNT  (0U)
#define DFT_SIZE            (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define SIGNAL_COUNT        (3U)
#define PI                  (3.14159265358979323846)
#define DEGREE_TO_RAD(x)    (((x) * PI) / 180.0)

typedef enum {
    WINDOW_RECTANGULAR = 0,
    WINDOW_HANN,
    WINDOW_HAMMING,
    WINDOW_BLACKMAN
} WINDOW_t;

/* Harmonic description */
typedef struct {
    double freqHz;
    double amp;
    double phaseDeg;
} harmonic_t;

/* Bin description */
typedef struct {
    uint16_t number;
    double freqHz;
} bin_t;

/* Complex result representation */
typedef struct {
    double imag;
    double real;
} dft_coeff_t;

typedef struct
{
    bool cosEnable;
    bool windowEnable;
} config_t;

static harmonic_t signal[SIGNAL_COUNT];
static config_t config;

static void AppInit(config_t* cfg)
{
    cfg->cosEnable = COS_ENABLE;
    cfg->windowEnable = WINDOW_ENANLE;
}

static bool HarmonicAdd(harmonic_t* h, double freqHz, double amp, double phaseDeg)
{
    bool result = false;

    for (uint8_t i = 0; i < SIGNAL_COUNT; i++)
    {
        if (h[i].freqHz == 0 && h[i].amp == 0 && h[i].phaseDeg == 0)
        {
            h[i].freqHz = freqHz;
            h[i].amp = amp;
            h[i].phaseDeg = phaseDeg;

            result = true;

            break;
        }
    }

    return result;
}

static void GenerateSamples(const harmonic_t* const harmonic, uint8_t harmCount, double* samples, uint16_t sampleCount)
{
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

static void ZeroPadding(double* samples, uint16_t sampleCount, uint16_t zeroCount)
{
    for (uint16_t i = 0; i < zeroCount; i++)
    {
        samples[sampleCount + i] = 0;
    }
}

static void GenerateBins(bin_t* const bins, uint16_t count)
{
    double binStep = FREQ_SAMPLE_HZ / (double)count;

    for (uint16_t i = 0; i < count; i++)
    {
        bins[i].number = i;
        bins[i].freqHz = (double)i * binStep;
    }
}

static void GenerateSinTemplate(uint16_t binNumber, double* const template, uint16_t nfft)
{
    double angle;

    for (uint16_t i = 0; i < nfft; i++)
    {
        angle = 2.0 * PI * (double)binNumber * (double)i / (double)nfft;
        template[i] = sin(angle);
    }
}

static void GenerateCosTemplate(uint16_t binNumber, double* const template, uint16_t nfft)
{
    double angle;

    for (uint16_t i = 0; i < nfft; i++)
    {
        angle = 2.0 * PI * (double)binNumber * (double)i / (double)nfft;
        template[i] = cos(angle);
    }
}

static double CompareTemplate(const double* const samples, const double* const template, uint16_t nfft)
{
    double result = 0.0;

    for (uint16_t i = 0; i < nfft; i++)
    {
        result += samples[i] * template[i];
    }

    return result;
}

static void CalculateDFT(const double* const samples, dft_coeff_t* const spectrum, uint16_t nfft)
{
    double sinTemplate[nfft];
    double cosTemplate[nfft];

    for (uint16_t i = 0; i < nfft; i++) {
        GenerateSinTemplate(i, sinTemplate, nfft);
        if (config.cosEnable)
        {
            GenerateCosTemplate(i, cosTemplate, nfft);
        }
        spectrum[i].imag = -CompareTemplate(samples, sinTemplate, nfft);
        if (config.cosEnable)
        {
            spectrum[i].real = CompareTemplate(samples, cosTemplate, nfft);
        }
    }
}

static double CoeffMagnitude(const dft_coeff_t* const value)
{
    return sqrt(value->imag * value->imag + value->real * value->real);
}

static void GenerateWindow(WINDOW_t type, double* window, uint16_t nfft)
{
    double phase;
    for (uint16_t i = 0; i < nfft; i++) {
        phase = 2.0 * PI * (double)i / (double)(nfft - 1U);

        switch (type) {
            case WINDOW_RECTANGULAR:
                window[i] = 1.0;
                break;

            case WINDOW_HANN:
                window[i] = 0.5 - 0.5 * cos(phase);
                break;

            case WINDOW_HAMMING:
                window[i] = 0.54 - 0.46 * cos(phase);
                break;

            case WINDOW_BLACKMAN:
                window[i] = 0.42 - 0.5 * cos(phase) + 0.08 * cos(2.0 * phase);
                break;

            default:
                window[i] = 1.0;
                break;
        }
    }
}

static void ApplyWindow(const double* const samples, const double* const window, double* const samplesWeighted, uint16_t nfft)
{
    for (uint16_t i = 0; i < nfft; i++)
    {
        samplesWeighted[i] = samples[i] * window[i];
    }
}

static void PrintSettings(void)
{
    printf("--------------------------\n");
    printf("Real signal application\n");
    printf("--------------------------\n");
    printf("Settings:\n");
    printf("Fs = %.2f Hz\n", FREQ_SAMPLE_HZ);
    printf("Real samples = %u\n", SAMPLE_COUNT);
    printf("Zero padding = %u\n", ZERO_PADDING_COUNT);
    printf("Bin step = %.3f Hz\n\n", FREQ_SAMPLE_HZ / (double)DFT_SIZE);
}

static void PrintSignalConfig(const harmonic_t* const harmonic, uint16_t count)
{
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

static void PrintSamples(const double* const samples, uint16_t nfft)
{
    double time_ms = 0.0;

    printf("Samples:\n");
    printf(" n | time, ms | x[n]\n");
    printf("---+----------+-----------\n");

    for (uint16_t i = 0; i < nfft; i++)
    {
        time_ms = 1000.0 * (double)i / FREQ_SAMPLE_HZ;
        printf("%2u | %8.3f | %9.4f\n", i, time_ms, samples[i]);
    }

    printf("\n");
}

static void PrintDFT(const bin_t* const bins, const dft_coeff_t* const spectrum, uint16_t nfft)
{
    printf("DFT result:\n");
    printf(" bin | frequency, Hz | sin result | cos result | magnitude\n");
    printf("-----+---------------+------------+------------+-----------\n");

    for (uint16_t i = 0; i < nfft; i++)
    {
        printf(" %3u | %13.3f | %10.4f | %10.4f | %9.4f\n",
                bins[i].number,
                bins[i].freqHz,
                spectrum[i].imag,
                spectrum[i].real,
                CoeffMagnitude(&spectrum[i]));
    }
}

static void SaveWindowDat(const double* samples, uint16_t nfft)
{
    FILE *fp = fopen("window.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint8_t i = 0; i < nfft; i++)
    {
        fprintf(fp, "%f\n", samples[i]);
    }
}

static void SaveInputDat(const double* samples, uint16_t nfft)
{
    FILE *fp = fopen("input.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < nfft; i++)
    {
        fprintf(fp, "%u %.9f %.12f\n" , i, (double)i/FREQ_SAMPLE_HZ, samples[i]);
    }

    fclose(fp);
}

static void SaveSpectrumDat(const bin_t* bins,const dft_coeff_t* spectrum, uint16_t nfft)
{
    FILE *fp = fopen("spectrum.dat", "w");
    if (!fp)
    {
        return;
    }

    for (uint16_t i = 0; i < nfft; i++)
    {
        fprintf(fp,"%u %.6f %.12f\n", bins[i].number, bins[i].freqHz, CoeffMagnitude(&spectrum[i]));
    }

    fclose(fp);
}

int main(void)
{
#if 0
    harmonic_t signal[SIGNAL_COUNT] = {
        { 1000.0, 1.0, 0.0 },
        { 2000.0, 0.5, 135.0 },
        { 3000.0, 0.0, 0.0 },
    };
#endif

    double samples[DFT_SIZE];
    double window[DFT_SIZE];
    double samplesWeighted[DFT_SIZE];
    bin_t bins[DFT_SIZE];
    dft_coeff_t spectrumRaw[DFT_SIZE];
    dft_coeff_t spectrumWeighted[DFT_SIZE];

    memset(samples, 0.0, sizeof(samples));
    memset(window, 0.0, sizeof(window));
    memset(samplesWeighted, 0.0, sizeof(samplesWeighted));
    memset(bins, 0.0, sizeof(bins));
    memset(spectrumRaw, 0.0, sizeof(spectrumRaw));
    memset(spectrumWeighted, 0.0, sizeof(spectrumWeighted));

    AppInit(&config);

    if (!HarmonicAdd(signal, 1000.0, 1.0, 0.0))
    {
        printf("Failed to add harmonic\n");
        return -1;
    }
#if 0
    if (!HarmonicAdd(signal, 2000.0, 1.0, 0.0))
    {
        printf("Failed to add harmonic\n");
        return -1;
    }

    if (!HarmonicAdd(signal, 3000.0, 1.0, 0.0))
    {
        printf("Failed to add harmonic\n");
        return -1;
    }

    if (!HarmonicAdd(signal, 4000.0, 1.0, 0.0))
    {
        printf("Failed to add harmonic\n");
        return -1;
    }
#endif

    PrintSettings();

    GenerateSamples(signal, SIGNAL_COUNT, samples, SAMPLE_COUNT);
    //ZeroPadding(samples, SAMPLE_COUNT, ZERO_PADDING_COUNT);

    GenerateBins(bins, DFT_SIZE);

    if (config.windowEnable)
    {
        GenerateWindow(WINDOW_HANN, window, DFT_SIZE);
        ApplyWindow(samples, window, samplesWeighted, DFT_SIZE);
        CalculateDFT(samplesWeighted, spectrumWeighted, DFT_SIZE);
    }

    CalculateDFT(samples, spectrumRaw, DFT_SIZE);

    PrintSignalConfig(signal, SIGNAL_COUNT);
    PrintSamples(samples, DFT_SIZE);
    PrintDFT(bins, spectrumRaw, DFT_SIZE);

    if (config.windowEnable)
    {
        PrintDFT(bins, spectrumWeighted, DFT_SIZE);
    }

    SaveInputDat(samples, DFT_SIZE);
    if (config.windowEnable)
    {
        SaveSpectrumDat(bins, spectrumWeighted, DFT_SIZE);
    }
    else
    {
        SaveSpectrumDat(bins, spectrumRaw, DFT_SIZE);
    }

    SaveWindowDat(samplesWeighted, DFT_SIZE);

    return 0;
}

/*
 * NOTE: Лайнос (стр. 102)
 * Окно должно накладываться только на исходные ненулевые отсчеты, иначе нулевые отсчеты приведут к тому,
 * что часть окна будет ообнулена и искажена, что приведет к ошибочным результатам.
 * */
