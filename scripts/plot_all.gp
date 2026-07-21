set term qt 0 title "Input signal"
set grid
plot "input.dat" using 2:3 with lines lw 2

set term qt 1 title "Window function"
set grid
plot "window.dat" with lines lw 2

set term qt 2 title "Spectrum"
set grid
plot "spectrum.dat" using 2:3 with impulses lw 3

pause mouse close