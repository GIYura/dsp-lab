set term qt 0 title "Convolution input"
set grid
set title "Input signal"
set xlabel "Sample"
set ylabel "Amplitude"
plot "output/input.dat" using 0:1 with linespoints lw 2 title "Input"

set term qt 1 title "Impulse response"
set grid
set title "Impulse response"
set xlabel "Sample"
set ylabel "Amplitude"
plot "output/impulse_response.dat" using 0:1 with impulses lw 2 title "h[n]"

set term qt 2 title "Convolution result"
set grid
set title "Convolution result"
set xlabel "Sample"
set ylabel "Amplitude"
plot "output/convolution.dat" using 0:1 with linespoints lw 2 title "y[n]"

pause mouse close
