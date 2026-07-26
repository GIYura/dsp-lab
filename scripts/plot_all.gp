# ============================================================
# Plot all generated data files
# ============================================================

file_input = "input.dat"
file_window = "window.dat"
file_windowed = "windowed.dat"
file_spectrum = "spectrum.dat"

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

    plot file_input using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_input)
}

#
# Window
#
if (file_exists(file_window)) {
    set term qt 1 title "Window function"
    set grid
    set xlabel "Sample index"
    set ylabel "Window coefficient"

    plot file_window using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_window)
}

#
# Windowed signal
#
if (file_exists(file_windowed)) {
    set term qt 2 title "Windowed signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_windowed using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_windowed)
}

#
# Spectrum
#
if (file_exists(file_spectrum)) {
    set term qt 3 title "Spectrum"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Raw FFT/DFT magnitude"

    plot file_spectrum using 2:3 with linespoints lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
}

pause mouse close