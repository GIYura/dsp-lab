# ============================================================
# SHIFT demo
# ============================================================

file_spectrum_orig = "output/spectrum.dat"
file_spectrum_shifted = "output/shifted_spectrum.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Spectrum shifted
#
if (file_exists(file_spectrum_shifted)) {
    set term qt 0 title "DFT Spectrum shifted"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    set xrange [-4000:4000]
    set xtics 1000

    plot file_spectrum_shifted using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_shifted)
    exit -1
}

#
# Spectrum orig
#
if (file_exists(file_spectrum_orig)) {
    set term qt 1 title "DFT Spectrum orig"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    set xrange [-4000:4000]
    set xtics 1000

    plot file_spectrum_orig using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_orig)
    exit -1
}

pause mouse close
