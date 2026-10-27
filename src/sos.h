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
bool SosAddSection(sos_t* const sos, double a1, double a2, double b0, double b1, double b2);
bool SosProcess(sos_t* const sos, const double* const in, double* const out, uint32_t count);
uint32_t SosGetSectionCount(const sos_t* const sos);

#endif /* SOS_H */
