# IQ Demo

Demonstrates real and complex I/Q representations of a generated harmonic signal.
The demo saves the I/Q trajectory and samples, then calculates a signed DFT spectrum to show the frequency direction of a complex exponential.

Build:
```
make iq
```

Run:
```
cd output
./iq_demo
```

Plot from the project root:
```
gnuplot scripts/iq_demo.gp
```
