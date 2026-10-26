# ============================================================
# Plot IIR Second complex pole order demo
# ============================================================

file_response = "output/response.dat"
file_pole1 = "output/pole1.dat"
file_pole2 = "output/pole2.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Response
#
if (file_exists(file_response)) {
    set term qt 0 title "Impulse response"
    set grid
    set xtics 2
    set xrange [0:50]
    set yrange [*:*]
    set xlabel "Sample"
    set ylabel "Amplitude"

    plot file_response using 0:1 with lines lw 2 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_response)
    #exit -1
}

#
# Poles
#
if (file_exists(file_pole1) && file_exists(file_pole2)) {

    set term qt 1 title "IIR Second Order - Poles"

    set grid
    set size ratio -1

    set xtics 0.2
    set ytics 0.2

    set xrange [-1.2:1.2]
    set yrange [-1.2:1.2]

    set xlabel "Re"
    set ylabel "Im"

    set xzeroaxis
    set yzeroaxis

    #
    # Unit circle
    #
    set parametric
    set trange [0:2*pi]
    set samples 360

    #
    # Plot
    #
    plot \
        cos(t), sin(t) with lines lw 2 title "Unit Circle", \
        file_pole1 using 1:2 with points pt 7 ps 2 title "Pole 1", \
        file_pole2 using 1:2 with points pt 7 ps 2 title "Pole 2"

} else {
    print "WARNING: Pole data files not found."

    if (!file_exists(file_pole1)) {
        print sprintf("WARNING: '%s' not found.", file_pole1)
    }

    if (!file_exists(file_pole2)) {
        print sprintf("WARNING: '%s' not found.", file_pole2)
    }
}

pause mouse close
