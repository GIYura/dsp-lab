# ============================================================
# Spectrum scale demo
# ============================================================

file_spectrum = "output/dft_spectrum.dat"

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
    set xlabel "Frequency (Hz)"
    set ylabel "Magnitude (dBFS)"
    set yrange [-120:0]

    plot file_spectrum using 2:3 with linespoints
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
    exit -1
}

pause mouse close
