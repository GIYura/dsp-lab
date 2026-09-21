# ============================================================
# Decimation demo
# ============================================================

file_spectrum_orig = "output/dft_spectrum_orig.dat"
file_spectrum_decimated = "output/dft_spectrum_decimated.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Spectrum orig
#
if (file_exists(file_spectrum_orig)) {
    set term qt 0 title "DFT Spectrum orig"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_orig using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_orig)
    exit -1
}

#
# Spectrum decimated
#
if (file_exists(file_spectrum_decimated)) {
    set term qt 3 title "DFT Spectrum decimated"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_decimated using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_decimated)
    exit -1
}

pause mouse close
