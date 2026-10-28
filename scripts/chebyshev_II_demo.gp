# ============================================================
# Chebyshev_II demo (4-order)
# ============================================================

file_response = "output/chebyshev_II_4_order_impulse_response.dat"
file_time_domain = "output/time_domain_signal.dat"
file_spectrum_before_filter = "output/spectrum_before_filter.dat"
file_spectrum_after_filter = "output/spectrum_after_filter.dat"

#
# Helper function:
#   returns 1 if file exists
#   returns 0 otherwise
#
file_exists(fname) = \
    (system(sprintf("test -f '%s'", fname)), GPVAL_SYSTEM_ERRNO == 0)

#
# Input signal
#
if (file_exists(file_time_domain)) {
    set term qt 0 title "Time-domain signal"
    set grid
    set xlabel "Sample"
    set ylabel "Amplitude"

    plot file_time_domain using 0:1 with linespoints pt 7 ps 0.7 lw 1 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_time_domain)
    exit -1
}

#
# Spectrum before Chebyshev_II 4-order filter
#
if (file_exists(file_spectrum_before_filter)) {
    set term qt 1 title "Spectrum before filter"
    set grid
    set xtics 1000
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_before_filter using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_before_filter)
    exit -1
}

#
# Spectrum after Chebyshev_II 4-order filter
#
if (file_exists(file_spectrum_after_filter)) {
    set term qt 2 title "Spectrum after filter"
    set grid
    set xtics 1000
    set xlabel "Frequency, Hz"
    set ylabel "Magnitude"

    plot file_spectrum_after_filter using 2:3 with lines lw 3 notitle
} else {
    print sprintf("WARNING: '%s' not found.", file_spectrum_after_filter)
    #exit -1
}

#
# Amplitude Frequency Characteristics biquad based on impulse response
#
if (file_exists(file_response)) {
    set term qt 3 title "Chebyshev_II 4-order impulse response"
    set grid
    set xrange [0:8000]
    set yrange [0:*]
    set xlabel "Frequency, Hz"
    set ylabel "Amplitude"

    plot file_response using 2:3 with lines lw 3 title "Chebyshev_II 4 order"
} else {
    print sprintf("WARNING: '%s' not found.", file_response)
    #exit -1
}

pause mouse close
