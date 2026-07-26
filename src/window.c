#include <assert.h>
#include <stddef.h>
#include <math.h>

#include "window.h"
#include "config.h"

void WindowGenerate(window_type_t type, double* const window, uint16_t size)
{
    assert(window != NULL);
    assert(size > 0U);

    if (size == 1)
    {
        window[0] = 1.0;
        return;
    }

    double phase;

    for (uint16_t i = 0; i < size; i++)
    {
        switch (type)
        {
            case WINDOW_RECTANGULAR:
                window[i] = 1.0;
                break;

            case WINDOW_HANN:
                phase = 2.0 * PI * (double)i / (double)(size - 1U);
                window[i] = 0.5 - 0.5 * cos(phase);
                break;

            case WINDOW_HAMMING:
                phase = 2.0 * PI * (double)i / (double)(size - 1U);
                window[i] = 0.54 - 0.46 * cos(phase);
                break;

            case WINDOW_BLACKMAN:
                phase = 2.0 * PI * (double)i / (double)(size - 1U);
                window[i] = 0.42 - 0.5 * cos(phase) + 0.08 * cos(2.0 * phase);
                break;

            default:
                window[i] = 1.0;
                break;
        }
    }
}

void WindowApply(const double* const samples, const double* const window, double* const samplesWeighted, uint16_t size)
{
    assert(samples != NULL);
    assert(window != NULL);
    assert(samplesWeighted != NULL);

    for (uint16_t i = 0; i < size; i++)
    {
        samplesWeighted[i] = samples[i] * window[i];
    }
}

