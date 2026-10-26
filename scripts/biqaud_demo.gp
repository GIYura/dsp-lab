# ============================================================
# Biquad demo
# ============================================================

file_amp_freq = "output/amp_freq_biqaud_impulse_response.dat"


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
if (file_exists(file_amp_freq)) {
    set term qt 0 title "Amp freq biquad impulse response"
    set grid
    set xrange [0:8000]
    set yrange [0:*]
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_amp_freq using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_amp_freq)
    #exit -1
}


pause mouse close
