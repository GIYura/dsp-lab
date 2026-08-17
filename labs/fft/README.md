# FFT Demo

Demonstrates radix-2 FFT on a generated multi-tone signal.
The demo saves the input samples and the raw spectrum magnitude for comparison and inspection.

Build:
```
make fft
```

Run:
```
cd output
./fft_demo
```

Plot from the project root:
```
gnuplot scripts/fft_demo.gp
```
