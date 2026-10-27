#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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

bool SosAddSection(sos_t* const sos, double a1, double a2, double b0, double b1, double b2)
{
    assert(sos != NULL);

    if (sos->count >= SOS_SECTIONS_MAX)
    {
        return false;
    }

    BiquadReset(&sos->sections[sos->count]);

    BiquadSetCoefficients(&sos->sections[sos->count], a1, a2, b0, b1, b2);

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
