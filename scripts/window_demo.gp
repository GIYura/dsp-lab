# ============================================================
# Plot window demo
# ============================================================

file_input = "output/input.dat"
file_window = "output/window.dat"
file_windowed = "output/windowed.dat"

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
# Window
#
if (file_exists(file_window)) {
    set term qt 1 title "Window function"
    set grid
    set xlabel "Sample"
	set ylabel "Weight"

    plot file_window using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_window)
    exit -1
}

#
# Windowed signal
#
if (file_exists(file_windowed)) {
    set term qt 2 title "Windowed signal"
    set grid
    set xlabel "Sample"
	set ylabel "Amplitude"

    plot file_windowed using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_windowed)
    exit -1
}

pause mouse close
