#ifndef FFT_H
#define FFT_H

#include <stdint.h>

#include "complex.h"
#include "config.h"

/*
 * Educational radix-2 FFT implementation for FFT_SIZE == 8.
 * The algorithm is intentionally divided into three explicit stages.
 */
//#if FFT_SIZE != 8U
//#error "Educational FFT implementation supports only FFT_SIZE == 8"
//#endif

typedef struct
{
    double sum_0_4;
    double sum_1_5;
    double sum_2_6;
    double sum_3_7;

    double diff_0_4;
    double diff_1_5;
    double diff_2_6;
    double diff_3_7;
} fft_stage1_t;

typedef struct
{
    complex_t a0;
    complex_t a1;
    complex_t a2;
    complex_t a3;

    complex_t b0;
    complex_t b1;
    complex_t b2;
    complex_t b3;
} fft_stage2_t;

/* Brief: Calculate first FFT stage
* [in] - samples - pointer to samples storage
* [out] - stage - pointer to first-stage result
* [out] - none
* */
void FFT_Stage1(const double* const samples, fft_stage1_t* const stage);

/* Brief: Calculate second FFT stage
* [in] - stage1 - pointer to first-stage result
* [out] - stage2 - pointer to second-stage result
* [out] - none
* */
void FFT_Stage2(const fft_stage1_t* const stage1, fft_stage2_t* const stage2);

/* Brief: Calculate third FFT stage
* [in] - stage2 - pointer to second-stage result
* [out] - spectrum - pointer to FFT spectrum storage
* [out] - none
* */
void FFT_Stage3(const fft_stage2_t* const stage2, complex_t* const spectrum);

/* Brief: Calculate complete 8-point FFT
* [in] - samples - pointer to samples storage
* [out] - spectrum - pointer to FFT spectrum storage
* [out] - none
* */
void FFT_Calculate(const double* const samples, complex_t* const spectrum);

/* Brief: Print first FFT stage
* [in] - stage - pointer to first-stage result
* [out] - none
* */
void FFT_PrintStage1(const fft_stage1_t* const stage);

/* Brief: Print second FFT stage
* [in] - stage - pointer to second-stage result
* [out] - none
* */
void FFT_PrintStage2(const fft_stage2_t* const stage);

/* Brief: Print FFT spectrum
* [in] - bins - pinter to FFT bins storage
* [in] - spectrum - pointer to FFT spectrum storage
* [in] - count - spectrum coefficient counter
* [out] - none
* */
void FFT_Print(const bin_t* const bins, const complex_t* const spectrum, uint16_t count);

/* Brief: Calculate FFT raw (unnormalized) magnitude
* [in] - spectrum - pointer to spectrum storage
* [out] - value
* */
double FFT_CalculateRawMagnitude(const complex_t* const spectrum);

/* Brief: Generate FFT bins
* [in] - bins - pointer to bin storage
* [in] - count - bin counter
* [out] - none
* */
void FFT_GenerateBins(bin_t* const bins, uint16_t count);

#endif /* FFT_H */



#if 0
#ifndef FFT_H
#define FFT_H

#include <stdint.h>
#include "complex.h"

typedef struct
{
    uint16_t number;
    double freqHz;
} fft_bin_t;

void FFT_Stage1(const double* const samples, complex_t* const spectrum, uint16_t count);
void FFT_Stage2(complex_t* const spectrum, uint16_t count);
void FFT_Stage3(complex_t* const spectrum, uint16_t count);
void FFT_Calculate(const double* const samples, complex_t* const spectrum, uint16_t count);
void FFT_GenerateBins(fft_bin_t* const bins, uint16_t count);
double FFT_CalculateRawMagnitude(const complex_t* const spectrum);
void FFT_Print(const fft_bin_t* const bins, const complex_t* const spectrum, uint16_t count);

#endif /* FFT_H */
#endif
