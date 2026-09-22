# ============================================================
# Coherent average demo
# ============================================================

file_clean = "output/clean.dat"
file_noisy = "output/noisy.dat"
file_averaged = "output/averaged.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Clean signal
#
if (file_exists(file_clean)) {
    set term qt 0 title "Clean signal"
    set grid
    set xlabel "Sample"
    set ylabel "Amplitude"

    plot file_clean using 0:1 with linespoints pt 7 ps 0.7 lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_clean)
    exit -1
}

#
# Noisy signal
#
if (file_exists(file_noisy)) {
    set term qt 1 title "Noisy signal"
    set grid
    set xlabel "Sample"
    set ylabel "Amplitude"

    plot file_noisy using 0:1 with linespoints pt 7 ps 0.7 lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_noisy)
    exit -1
}

#
# Averaged signal
#
if (file_exists(file_averaged)) {
    set term qt 2 title "Averaged signal"
    set grid
    set xlabel "Sample"
    set ylabel "Amplitude"

    plot file_averaged using 0:1 with linespoints pt 7 ps 0.7 lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_averaged)
    exit -1
}

pause mouse close
