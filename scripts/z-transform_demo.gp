# ============================================================
# Z-Transform demo
# ============================================================

file_z_trans = "output/z-trans.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Amplitude Frequency Characteristics
#
if (file_exists(file_z_trans)) {
    set term qt 0 title "Z-Transform - IIR Frequency Response"
    set grid
    set xrange [0:8000]
    set yrange [0:1.05]
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_z_trans using 1:2 with lines lw 3 title "IIR |H(f)|"
} else {
    print sprintf("WARNING: '%s' not found.", file_z_trans)
    exit -1
}

pause mouse close