# ============================================================
# Plot interpolation demo
# ============================================================

file_spectrum_orig = "output/dft_spectrum_orig.dat"
file_spectrum_zero_stuffed = "output/dft_spectrum_zero_stuffed.dat"
file_spectrum_interpolated = "output/dft_spectrum_interpolated.dat"

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
# Spectrum zero-stuffed
#
if (file_exists(file_spectrum_zero_stuffed)) {
    set term qt 1 title "DFT Spectrum zero-stuffed"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_zero_stuffed using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_zero_stuffed)
    exit -1
}

#
# Spectrum interpolated
#
if (file_exists(file_spectrum_interpolated)) {
    set term qt 2 title "DFT Spectrum interpolated"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"
    set yrange [0:65]

    plot file_spectrum_interpolated using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_interpolated)
    exit -1
}

pause mouse close
