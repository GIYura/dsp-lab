/*
 * IIR Second order complex poles demo
 * */

#include <stdio.h>

#include "config.h"
#include "iir.h"
#include "save.h"

/* Demo config */
#define FREQ_SAMPLE_HZ          (16000.0)
#define RESPONSE_SIZE           (1024)

int main(void)
{
    IIR_Second_Order_t filter;
    double impulse[RESPONSE_SIZE] = {0};
    double a, b0, b1;
    double response[RESPONSE_SIZE] = {0};
    complex_t poles[2];
    double polesModule[2];
    double polesAngle[2];
    double filterFrequency;

    impulse[0] = 1.0;
    a = 1.0;
    b0 = 0.3;
    b1 = -1.1;

    IIR_SecondOrderInit(&filter);
    IIR_SecondOrderSetCoefficients(&filter, a, b0, b1);
    IIR_SecondOrderPrint(&filter);
    IIR_SecondOrderCalculate(&filter, impulse, response, RESPONSE_SIZE);

    IIR_SecondOrderPoles(filter.b[0], filter.b[1], &poles[0], &poles[1]);

    printf("Pole 1 = Re[%.3f] Im[%.3f]\n", poles[0].real, poles[0].imag);
    printf("Pole 2 = Re[%.3f] Im[%.3f]\n", poles[1].real, poles[1].imag);

    polesModule[0] = IIR_SecondOrderPoleModule(&poles[0]);
    polesModule[1] = IIR_SecondOrderPoleModule(&poles[1]);

    printf("Pole 1 module = %.3f\n", polesModule[0]);
    printf("Pole 2 module = %.3f\n", polesModule[1]);
    printf("Stability: %s\n", IIR_SecondOrderStability(polesModule[0], polesModule[1]));

    polesAngle[0] = IIR_SecondOrderPoleAngle(&poles[0]);
    polesAngle[1] = IIR_SecondOrderPoleAngle(&poles[1]);

    printf("Pole 1 angle (deg) = %.3f\n", RAD_TO_DEGREE(polesAngle[0]));
    printf("Pole 2 angle (deg) = %.3f\n", RAD_TO_DEGREE(polesAngle[1]));

    filterFrequency = IIR_SecondOrderSelfFreq(polesAngle[0], FREQ_SAMPLE_HZ);
    printf("IIR self frequency = %.3f Hz\n", filterFrequency);

    SaveDat("response.dat", response, RESPONSE_SIZE);
    SaveXYDat("pole1.dat", &poles[0].real, &poles[0].imag, 1);
    SaveXYDat("pole2.dat", &poles[1].real, &poles[1].imag, 1);

    return 0;
}
