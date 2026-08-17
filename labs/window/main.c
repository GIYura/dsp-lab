#include "config.h"
#include "output.h"
#include "signal.h"
#include "window.h"

int main(void)
{
    harmonic_t signal[HARMONIC_COUNT] = {0};
    double samples[SAMPLE_COUNT] = {0};
    double window[SAMPLE_COUNT];
    double weighted[SAMPLE_COUNT];

    SignalHarmonicAdd(signal, 1000.0, 1.0, 0.0);
    SignalHarmonicAdd(signal, 2000.0, 0.0, 0.0);
    SignalHarmonicAdd(signal, 3000.0, 0.0, 0.0);

    SignalGenerateSamples(signal, HARMONIC_COUNT, samples, SAMPLE_COUNT);
    WindowGenerate(WINDOW_HANN, window, SAMPLE_COUNT);
    WindowApply(samples, window, weighted, SAMPLE_COUNT);

    SaveDat("input.dat", samples, SAMPLE_COUNT);
    SaveDat("window.dat", window, SAMPLE_COUNT);
    SaveDat("windowed.dat", weighted, SAMPLE_COUNT);

    return 0;
}
