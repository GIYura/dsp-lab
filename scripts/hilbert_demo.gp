# ============================================================
# Hilbert demo
# ============================================================

file_cos = "output/cos.dat"
file_sin = "output/sin.dat"
file_cos_delay = "output/cos_delay.dat"
file_spectrum = "output/dft_iq_spectrum.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Cos signal
#
if (file_exists(file_cos)) {
    set term qt 0 title "Cos signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_cos using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_cos)
    exit -1
}

#
# Sin signal
#
if (file_exists(file_sin)) {
    set term qt 1 title "Sin signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_sin using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_sin)
    exit -1
}

#
# Cos delayed signal
#
if (file_exists(file_cos_delay)) {
    set term qt 2 title "Cos delayed signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_cos_delay using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_cos_delay)
    exit -1
}

#
# Cos delayed signal + sin
#
if (file_exists(file_cos_delay) && file_exists(file_sin)) {
    set term qt 3 title "Cos delayed + Hilbert signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_cos_delay using 0:1 with lines title "I - delayed cos", file_sin using 0:1 with lines title "Q - Hilbert"
} else {
    print sprintf("WARNING: '%s' not found.", file_cos_delay)
    exit -1
}

#
# Spectrum
#
if (file_exists(file_spectrum)) {
    set term qt 4 title "DFT Spectrum"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
    exit -1
}


pause mouse close