#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

typedef enum
{
    WINDOW_RECTANGULAR = 0,
    WINDOW_HANN,
    WINDOW_HAMMING,
    WINDOW_BLACKMAN
} window_type_t;

/* Brief: Generate window function
* [in] - type - window type
* [in] - window - pointer to window function
* [in] - size - window size
* [out] - none
* */
void WindowGenerate(window_type_t type, double* const window, uint16_t size);

/* Brief: Apply window function to samples
 * NOTE: Лайнос (стр. 102)
 * Окно должно накладываться только на исходные ненулевые отсчеты, иначе нулевые отсчеты приведут к тому,
 * что часть окна будет ообнулена и искажена, что приведет к ошибочным результатам.
* [in] - samples - pointer to samples storage
* [in] - window - pointer to window function
* [in] - samplesWeighted - pointer to windowed samples storage
* [in] - size - window size
* [out] - none
* */
void WindowApply(const double* const samples, const double* const window, double* const samplesWeighted, uint16_t size);

#endif /* WINDOW_H */
