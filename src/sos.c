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

bool SosAddSection(sos_t* const sos, const biquad_t* const section)
{
    assert(sos != NULL);
    assert(section != NULL);

    if (sos->count == SOS_SECTIONS_MAX)
    {
        return false;
    }

    BiquadReset(&sos->sections[sos->count]);

    memcpy(&sos->sections[sos->count], section, sizeof(biquad_t));
    ++sos->count;

    return true;
}

void SosProcess(sos_t* const sos)
{
    assert(sos != NULL);

}


