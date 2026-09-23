## Non-Coherent Averaging

This lab demonstrates non-coherent averaging in the frequency domain.

Multiple records containing the same harmonic with different random phases and independent noise realizations are transformed using the DFT.
The power spectrum pow2|X[k]| is calculated for each record and averaged across multiple measurements.

The experiment compares averaging with N = 1, 10, and 100 and demonstrates how increasing the number of averages reduces fluctuations in the estimated noise power while preserving the spectral components of the signal.

Build:
```
make non_coherent_avg
```

Run:
```
cd output
./non_coherent_avg 1 / 10 / 100
```

Plot from the project root:
```
gnuplot scripts/non_coherent_avg_demo.gp
```
