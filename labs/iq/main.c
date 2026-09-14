#include <stdio.h>

#include "signal.h"
#include "config.h"
#include "complex.h"
#include "output.h"
#include "dft.h"

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT];
    complex_t iq[SAMPLE_COUNT];
    complex_t spectrum[DFT_SIZE];
    bin_t bins[DFT_SIZE];

    /* Create signal */
    SignalHarmonicAdd(signal, (-1000.0), 1.0, 0.0);
    SignalHarmonicAdd(signal, (3000.0), 0.0, 0.0);
    SignalHarmonicAdd(signal, (5000.0), 0.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    SignalPrintSamples(samples, SAMPLE_COUNT);
    SaveDat("real.dat", samples, SAMPLE_COUNT);

    SignalGenerateIQSamples(signal, HARMONIC_COUNT, iq, SAMPLE_COUNT);
    SignalPrintIQSamples(iq, SAMPLE_COUNT);
    SaveIQDat("iq.dat", iq, SAMPLE_COUNT);

    /**/
    DFT_GenerateBins(bins, DFT_SIZE);
    DFT_CalculateComplex(iq, spectrum, DFT_SIZE);
    DFT_Print(bins, spectrum, DFT_SIZE);
    SaveSpectrumDat("dft_iq_spectrum.dat", bins, spectrum, DFT_CalculateRawMagnitude, DFT_SIZE);

    return 0;
}
