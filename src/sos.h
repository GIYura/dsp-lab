#ifndef SOS_H
#define SOS_H

#define SOS_SECTIONS_MAX    (8)

#include <stdbool.h>

#include "biquad.h"

typedef struct
{
    biquad_t sections[SOS_SECTIONS_MAX];
    uint32_t count;
} sos_t;

void SosInit(sos_t* const sos);
void SosReset(sos_t* const sos);
bool SosAddSection(sos_t* const sos, const biquad_t* const section);
void SosProcess(sos_t* const sos);

#endif /* SOS_H */
