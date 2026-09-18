# IIR Demo

Demonstrates a simple low-pass IIR filter applied twice to a generated multi-tone signal.
The demo compares signed DFT spectra before and after filtering and plots the filter amplitude-frequency response.

Build:
```
make iir
```

Run:
```
cd output
./iir_demo
```

Plot from the project root:
```
gnuplot scripts/iir_demo.gp
```
