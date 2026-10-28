# ============================================================
# Butterworth float vs double demo
# ============================================================

file_amp_freq_double = "output/amp_freq_butterworth_impulse_response_double.dat"
file_amp_freq_float = "output/amp_freq_butterworth_impulse_response_float.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Amplitude Frequency Characteristics biquad based on impulse response
#
if (file_exists(file_amp_freq_double)) {
    set term qt 0 title "Amp freq Butterworth impulse response"
    set grid
    set xrange [0:8000]
    set yrange [0:1.2]
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_amp_freq_double using 2:3 with lines lw 3 title "Butterworth 6 order double"
} else {
    print sprintf("WARNING: '%s' not found.", file_amp_freq_double)
    #exit -1
}

#
# Amplitude Frequency Characteristics biquad based on impulse response
#
if (file_exists(file_amp_freq_float)) {
    set term qt 1 title "Amp freq Butterworth impulse response"
    set grid
    set xrange [0:8000]
    set yrange [0:1.2]
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_amp_freq_float using 2:3 with lines lw 3 title "Butterworth 6 order float"
} else {
    print sprintf("WARNING: '%s' not found.", file_amp_freq_float)
    #exit -1
}

pause mouse close
