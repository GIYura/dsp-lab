# Decimation Demo

Demonstrates integer decimation by keeping every second sample of a two-tone real signal.
The demo compares time-domain samples and signed DFT spectra before and after decimation, making aliasing visible when the 3 kHz component folds into the reduced Nyquist band.

Build:
```
make decimation
```

Run:
```
cd output
./decimation_demo
```

Plot from the project root:
```
gnuplot scripts/decimation_demo.gp
```
