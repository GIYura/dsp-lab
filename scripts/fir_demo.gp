# ============================================================
# Plot FIR demo
# ============================================================

file_spectrum_before = "output/spectrum_before_fir.dat"
file_spectrum_after = "output/spectrum_after_fir.dat"
file_amp_freq = "output/amp_freq_fir.dat"
file_input = "output/input.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Spectrum before FIR
#
if (file_exists(file_spectrum_before)) {
    set term qt 0 title "DFT Spectrum before FIR"
    set grid
    set xtics 1
    set xlabel "Frequency, kHz"
	set ylabel "Magnitude"

    plot file_spectrum_before using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_before)
    #exit -1
}

#
# Spectrum after FIR
#
if (file_exists(file_spectrum_after)) {
    set term qt 1 title "DFT Spectrum after FIR"
    set grid
    set xtics 1
    set xlabel "Frequency, kHz"
	set ylabel "Magnitude"

    plot file_spectrum_after using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_after)
    #exit -1
}

#
# Amplitude Frequency Characteristics FIR
#
if (file_exists(file_amp_freq)) {
    set term qt 2 title "Amp freq FIR"
    set grid
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_amp_freq using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_amp_freq)
    #exit -1
}

#
# Input signal
#
if (file_exists(file_input)) {
    set term qt 3 title "Input signal"
    set grid
    set xtics 10
    set xrange [0:150]
    set yrange [-3:3]
    set xlabel "Time, ms"
    set ylabel "Amplitude"

    plot file_input using 0:1 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_input)
    #exit -1
}


pause mouse close
