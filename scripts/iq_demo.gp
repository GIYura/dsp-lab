# ============================================================
# IQ demo
# ============================================================

real_input = "output/real.dat"
iq_input = "output/iq.dat"
file_spectrum = "output/dft_iq_spectrum.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Real signal
#
if (file_exists(real_input)) {
    set term qt 0 title "Real signal"
    set grid
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot real_input using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", real_input)
    exit -1
}

#
# IQ plane
#
if (file_exists(iq_input)) {
    set term qt 1 title "IQ plane"
    set grid
    set xlabel "I"
    set ylabel "Q"

    plot iq_input using 1:2:3:4 with vectors filled head title "direction"
} else {
    print sprintf("WARNING: '%s' not found.", iq_input)
    exit -1
}

#
# IQ samples
#
if (file_exists(iq_input)) {
    set term qt 2 title "IQ samples"
    set grid
    set xlabel "Sample n"
    set ylabel "Amplitude"

    plot iq_input using 0:1 with linespoints lw 2 title "I", iq_input using 0:2 with linespoints lw 2 title "Q"
} else {
    print sprintf("WARNING: '%s' not found.", iq_input)
    exit -1
}

#
# Spectrum
#
if (file_exists(file_spectrum)) {
    set term qt 3 title "DFT Spectrum"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    Fs = 8.0      # kHz
    Nyquist = Fs / 2.0

    set xrange [-Nyquist:Nyquist]
    set xtics 1
    set xlabel "Frequency, kHz"

    plot file_spectrum using (($2 >= Nyquist) ? ($2 - Fs) : $2):3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum)
    exit -1
}

pause mouse close
