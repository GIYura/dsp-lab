# ============================================================
# Plot all generated data files in one window
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
# Single Qt window
#
set term qt 0 size 1400,900 title "DSP plots" persist

set grid
set border linewidth 1
set key off

#
# Four plots in one window
#
set multiplot layout 2,2 rowsfirst title "DSP signal analysis"

#
# Plot 1: Input signal
#
if (file_exists(file_input)) {
    set title "Input signal"
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_input using 2:3 with lines lw 2
} else {
    print sprintf("WARNING: '%s' not found.", file_input)

    set title "Input signal — file not found"
    unset xlabel
    unset ylabel
    plot NaN notitle
}

#
# Plot 2: Window function
#
if (file_exists(file_window)) {
    set title "Window function"
    set xlabel "Sample index"
    set ylabel "Window coefficient"

    plot file_window using 0:1 with lines lw 2
} else {
    print sprintf("WARNING: '%s' not found.", file_window)

    set title "Window function — file not found"
    unset xlabel
    unset ylabel
    plot NaN notitle
}

#
# Plot 3: Windowed signal
#
if (file_exists(file_windowed)) {
    set title "Windowed signal"
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_windowed using 2:3 with lines lw 2
} else {
    print sprintf("WARNING: '%s' not found.", file_windowed)

    set title "Windowed signal — file not found"
    unset xlabel
    unset ylabel
    plot NaN notitle
}

#
# Plot 4: Spectrum
#
if (file_exists(file_spectrum)) {
    set title "Spectrum"
    set xlabel "Frequency, Hz"
    set ylabel "Raw FFT/DFT magnitude"

    plot file_spectrum using 2:3 with linespoints lw 2 pt 7 ps 0.5
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)

    set title "Spectrum — file not found"
    unset xlabel
    unset ylabel
    plot NaN notitle
}

unset multiplot

pause mouse close