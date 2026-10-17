/*
 * IIR single pole Z-transform
 * */

#include "config.h"
#include "iir.h"
#include "save.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (16000.0)
#define ZERO_PADDING_COUNT      (0U)
#define DFT_SIZE                (SAMPLE_COUNT + ZERO_PADDING_COUNT)
#define LPF_CUT_OFF_HZ          (3000.0)
#define Z_TRANS_SIZE            (RESPONSE_SIZE / 2 + 1)

int main(void)
{
    iir_t filter;
    double outFreq[Z_TRANS_SIZE];
    double outMagnitude[Z_TRANS_SIZE];

    /* Generate LPF */
    IIR_LowPassGenerate(&filter, FREQ_SAMPLE_HZ, LPF_CUT_OFF_HZ);
    IIR_Print(&filter);

    /* Apply Z-Transform */
    IIR_Z_Transform(filter.a, filter.b, outFreq, outMagnitude, FREQ_SAMPLE_HZ, RESPONSE_SIZE);

    SaveXYDat("z-trans.dat", outFreq, outMagnitude, Z_TRANS_SIZE);

    return 0;
}
