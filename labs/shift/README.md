# Frequency Shift Demo

Demonstrates frequency translation by multiplying a real input signal by a complex oscillator.
The demo compares signed DFT spectra before and after the complex frequency shift.

Build:
```
make shift
```

Run:
```
cd output
./shift_demo
```

Plot from the project root:
```
gnuplot scripts/shift_demo.gp
```
