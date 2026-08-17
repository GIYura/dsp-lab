# ============================================================
# Plot DFT demo
# ============================================================

file_input = "output/input.dat"
file_spectrum = "output/spectrum.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Input signal
#
if (file_exists(file_input)) {
    set term qt 0 title "Input signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_input using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_input)
    exit -1
}

#
# Spectrum
#
if (file_exists(file_spectrum)) {
    set term qt 1 title "DFT Spectrum"
    set grid
    set xlabel "Frequency, Hz"
	set ylabel "Magnitude"

    plot file_spectrum using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
    exit -1
}

pause mouse close
