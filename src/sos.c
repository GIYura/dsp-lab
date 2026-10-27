#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "sos.h"

void SosInit(sos_t* const sos)
{
    assert(sos != NULL);

    sos->count = 0;

    for (uint32_t i = 0; i < SOS_SECTIONS_MAX; i++)
    {
        BiquadInit(&sos->sections[i]);
    }
}

void SosReset(sos_t* const sos)
{
    assert(sos != NULL);

    for (uint32_t i = 0; i < sos->count; i++)
    {
        BiquadReset(&sos->sections[i]);
    }
}

bool SosAddSection(sos_t* const sos, double b0, double b1, double b2, double a0, double a1, double a2)
{
    assert(sos != NULL);

    double b0_normalized;
    double b1_normalized;
    double b2_normalized;
    double a1_normalized;
    double a2_normalized;

    if (sos->count >= SOS_SECTIONS_MAX)
    {
        return false;
    }

    if ( (!isfinite(b0)) ||
         (!isfinite(b1)) ||
         (!isfinite(b2)) ||
         (!isfinite(a0)) ||
         (!isfinite(a1)) ||
         (!isfinite(a2)))
    {
        return false;
    }

    if (a0 == 0)
    {
        return false;
    }

    b0_normalized = b0 / a0;
    b1_normalized = b1 / a0;
    b2_normalized = b2 / a0;
    a1_normalized = a1 / a0;
    a2_normalized = a2 / a0;

    if ( (!isfinite(b0_normalized)) ||
         (!isfinite(b1_normalized)) ||
         (!isfinite(b2_normalized)) ||
         (!isfinite(a1_normalized)) ||
         (!isfinite(a2_normalized)))
    {
        return false;
    }

    BiquadReset(&sos->sections[sos->count]);

    BiquadSetCoefficients(&sos->sections[sos->count],
                          a1_normalized,
                          a2_normalized,
                          b0_normalized,
                          b1_normalized,
                          b2_normalized);

    ++sos->count;

    return true;
}

bool SosProcess(sos_t* const sos, const double* const in, double* const out, uint32_t count)
{
    assert(sos != NULL);
    assert(in != NULL);
    assert(out != NULL);

    double sample;

    if (sos->count == 0)
    {
        return false;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        sample = in[i];

        for (uint32_t j = 0; j < sos->count; j++)
        {
            BiquadProcess(&sos->sections[j], &sample, &sample, 1);
        }

        out[i] = sample;
    }

    return true;
}

uint32_t SosGetSectionCount(const sos_t* const sos)
{
    assert(sos != NULL);

    return sos->count;
}
