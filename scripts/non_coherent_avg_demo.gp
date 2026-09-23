# ============================================================
# Non-coherent averaging demo
# ============================================================

file_power_001 = "output/power_001.dat"
file_power_010 = "output/power_010.dat"
file_power_100 = "output/power_100.dat"

Fs = 8000.0
N  = 64

bin_width = Fs / N

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# N = 1
#
if (file_exists(file_power_001)) {
    set term qt 0 title "Non-coherent averaging: N = 1"
    set grid
    set xlabel "Frequency (Hz)"
    set ylabel "Power"
    set xrange [-Fs/2:Fs/2]

    plot file_power_001 \
        using (($0 - N/2) * bin_width):1 \
        with lines lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_power_001)
    exit -1
}

#
# N = 10
#
if (file_exists(file_power_010)) {
    set term qt 1 title "Non-coherent averaging: N = 10"
    set grid
    set xlabel "Frequency (Hz)"
    set ylabel "Power"
    set xrange [-Fs/2:Fs/2]

    plot file_power_010 \
        using (($0 - N/2) * bin_width):1 \
        with lines lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_power_010)
    exit -1
}

#
# N = 100
#
if (file_exists(file_power_100)) {
    set term qt 2 title "Non-coherent averaging: N = 100"
    set grid
    set xlabel "Frequency (Hz)"
    set ylabel "Power"
    set xrange [-Fs/2:Fs/2]

    plot file_power_100 \
        using (($0 - N/2) * bin_width):1 \
        with lines lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_power_100)
    exit -1
}

pause mouse close