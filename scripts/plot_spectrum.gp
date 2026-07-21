set term qt 0 title "Spectrum"
set grid
set title "Input signal"
plot "spectrum.dat" using 2:3 with impulses lw 3

pause -1
