# ============================================================
# Plot spectrum generated data files
# ============================================================

file_spectrum = "spectrum.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Spectrum
#
if (file_exists(file_spectrum)) {
    set term qt 3 title "Spectrum"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Raw FFT/DFT magnitude"

    plot file_spectrum using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
    exit -1
}

pause mouse close
