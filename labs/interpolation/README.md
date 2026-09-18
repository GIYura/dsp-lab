# Interpolation Demo

Demonstrates interpolation by injecting zero (depends on factor) single-tone real signal.
The demo compares time-domain samples and signed DFT spectra before and after interpolation, making images visible (+-3 kHz component) appears in 
new Nuquist band.

Build:
```
make interpolation
```

Run:
```
cd output
./interpolation_demo
```

Plot from the project root:
```
gnuplot scripts/interpolation_demo.gp
```
