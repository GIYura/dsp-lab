# ============================================================
# Decimation demo
# ============================================================

file_orig = "output/orig.dat"
file_decimated = "output/decimated.dat"
file_spectrum_1 = "output/dft_spectrum_1.dat"
file_spectrum_2 = "output/dft_spectrum_2.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Before decimation signal
#
if (file_exists(file_orig)) {
    set term qt 0 title "Orig signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    #plot file_orig using 0:1 with lines lw 3 notitle
    plot file_orig using ($1*1000):2 with linespoints
} else {
    print sprintf("WARNING: '%s' not found.", file_orig)
    exit -1
}

#
# After decimation signal
#
if (file_exists(file_decimated)) {
    set term qt 1 title "Decimated signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    #plot file_decimated using 0:1 with lines lw 3 notitle
    plot file_decimated using ($1*1000):2 with linespoints
} else {
    print sprintf("WARNING: '%s' not found.", file_decimated)
    exit -1
}

#
# Spectrum #1
#
if (file_exists(file_spectrum_1)) {
    set term qt 2 title "DFT Spectrum #1"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_1 using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_1)
    exit -1
}

#
# Spectrum #2
#
if (file_exists(file_spectrum_2)) {
    set term qt 3 title "DFT Spectrum #2"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_2 using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_2)
    exit -1
}

pause mouse close
