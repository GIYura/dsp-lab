# ============================================================
# Plot windowed signal generated data files
# ============================================================

file_windowed = "windowed.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

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
    exit -1
}

pause mouse close