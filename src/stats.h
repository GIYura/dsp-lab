#ifndef STATS_H
#define STATS_H

#include <stdint.h>

double StatsMean(const double* const samples, uint32_t count);
double StatsStandardDeviation(const double* const samples, uint32_t count);

#endif /* STATS_H */
