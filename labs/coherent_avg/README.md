## Coherent Averaging

This lab demonstrates how coherent averaging improves the signal-to-noise ratio (SNR) of a signal corrupted by random noise.

Multiple records containing the same coherent signal with different random noise realizations are averaged sample by sample. 
The lab measures the noise standard deviation and SNR before and after averaging and compares the measured SNR improvement with the theoretical factor of sqrt(N).

Build:
```
make coherent_avg
```

Run:
```
cd output
./coherent_demo_avg
```

Plot from the project root:
```
gnuplot scripts/coherent_avg_demo.gp
```
