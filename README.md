## Description 

Digital Signal Processing (DSP) laboratory written in C.

The project currently includes signal generation, window functions,
DFT calculation and spectrum visualization using Gnuplot.

FFT, FIR/IIR filters, convolution and correlation will be added
as the project evolves.

### Build

```
make
```

### Run

```
./dsp-lab
```

### Display graphs

1. Run command below to see options

```
make help
```

2. Show DFT/FFT graphs

```
make plot_dft_fft_all
```

3. Show individual graphs

```
make plot_in
make plot_window
make plot_windowed
make plot_spectrum
```