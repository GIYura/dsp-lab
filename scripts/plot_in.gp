# ============================================================
# Plot input generated data files
# ============================================================

file_input = "input.dat"

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
    exit -1
}

pause mouse close