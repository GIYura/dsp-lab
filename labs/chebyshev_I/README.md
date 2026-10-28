## Chebyshev_I 4-order demo

### How-to

1. Run pyDFA and set following settings:
- Response type: lowpass
- Filter design: Chebyshev_I
- Frequency unit: Hz
- Amplitude unit: dB
- Sample frequency: 16000 Hz
- Passband edge: 2000 Hz
- Stopband edge: 4000 Hz
- Passband ripple: 1 dB
- Stopband ripple: 40 dB
- Filter order: Auto

2. Click button 'Design Filter'

3. Navigate to 'Analysis' and click 'Copy SOS'

4. Apply copied coefficients to /lab/chebyshev_I/main.c

5. Build application
```
make chebyshev_I
```

6. Run application
```
./chebyshev_I_demo
```

7. Run gnuplot script
```
gnuplot scripts/chebyshev_I_demo.gp 
```