# Hilbert Transform Demo

Demonstrates an FIR Hilbert transformer used to create the quadrature component of a real cosine.
The original branch is delayed by the FIR group delay, combined with the Hilbert output into an analytic I/Q signal, and inspected with a signed DFT spectrum.

Build:
```
make hilbert
```

Run:
```
cd output
./hilbert_demo
```

Plot from the project root:
```
gnuplot scripts/hilbert_demo.gp
```
