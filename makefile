CC := gcc
RM := rm -rf

CFLAGS := -std=c99 -g -O0 -Wall -Wpedantic -Wextra -Isrc
LDLIBS := -lm

OUTDIR := output

DFT := $(OUTDIR)/dft_demo
FFT := $(OUTDIR)/fft_demo
WINDOW := $(OUTDIR)/window_demo
CONV := $(OUTDIR)/convolution_demo
FIR := $(OUTDIR)/fir_demo
IIR_1_ORDER := $(OUTDIR)/iir_1_order_demo
IIR_2_ORDER := $(OUTDIR)/iir_2_order_demo
IIR_2_ORDER_COMPLEX_POLE := $(OUTDIR)/iir_2_order_demo_complex_pole
IQ := $(OUTDIR)/iq_demo
SHIFT := $(OUTDIR)/shift_demo
HILBERT := $(OUTDIR)/hilbert_demo
DECIMATION := $(OUTDIR)/decimation_demo
INTERPOLATION := $(OUTDIR)/interpolation_demo
COHERENT_AVG := $(OUTDIR)/coherent_avg_demo
NON_COHERENT_AVG := $(OUTDIR)/non_coherent_avg_demo
SPECTRUM_SCALE := $(OUTDIR)/spectrum_scale_demo
MAG_APPROX := $(OUTDIR)/magnitude_approximation_demo
COMPLEX_MUL := $(OUTDIR)/complex_mul_demo
RESTORE_SPECTRUM := $(OUTDIR)/restore_spectrum_demo
SPECTRUM_PEAK := $(OUTDIR)/spectrum_peak_demo
BIQUAD := $(OUTDIR)/biquad_demo
BUTTERWORTH := $(OUTDIR)/butterworth_demo
BUTTERWORTH_FLOAT_VS_DOUBLE := $(OUTDIR)/butterworth_float_vs_double_demo
CHEBYSHEV_I := $(OUTDIR)/chebyshev_I_demo
CHEBYSHEV_II := $(OUTDIR)/chebyshev_II_demo
ELLIPTIC := $(OUTDIR)/elliptic_demo

.PHONY: all dft fft window convolution biquad butterworth chebyshev_I chebyshev_II elliptic butterworth_float_vs_double fir iir_1_order iir_2_order iir_2_order_complex_pole iq shift hilbert decimation interpolation coherent_avg non_coherent_avg spectrum_scale magnitude_approximation complex_mul restore_spectrum spectrum_peak clean help

all: dft fft window convolution biquad butterworth chebyshev_I chebyshev_II elliptic butterworth_float_vs_double fir iir_1_order iir_2_order iir_2_order_complex_pole iq shift hilbert decimation interpolation coherent_avg non_coherent_avg spectrum_scale magnitude_approximation complex_mul restore_spectrum spectrum_peak

dft: $(DFT)

fft: $(FFT)

window: $(WINDOW)

convolution: $(CONV)

fir: $(FIR)

iir_1_order: $(IIR_1_ORDER)

iir_2_order: $(IIR_2_ORDER)

iir_2_order_complex_pole: $(IIR_2_ORDER_COMPLEX_POLE)

iq: $(IQ)

shift: $(SHIFT)

hilbert: $(HILBERT)

decimation: $(DECIMATION)

interpolation: $(INTERPOLATION)

coherent_avg: $(COHERENT_AVG)

non_coherent_avg: $(NON_COHERENT_AVG)

spectrum_scale: $(SPECTRUM_SCALE)

magnitude_approximation: $(MAG_APPROX)

complex_mul: $(COMPLEX_MUL)

restore_spectrum: $(RESTORE_SPECTRUM)

spectrum_peak: $(SPECTRUM_PEAK)

biquad: $(BIQUAD)

butterworth: $(BUTTERWORTH)

butterworth_float_vs_double: $(BUTTERWORTH_FLOAT_VS_DOUBLE)

chebyshev_I: $(CHEBYSHEV_I)

chebyshev_II: $(CHEBYSHEV_II)

elliptic: $(ELLIPTIC)

$(OUTDIR):
	@mkdir -p $@

$(DFT): labs/dft/main.c src/dft.c src/config.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| DFT                          | Done! |'

$(FFT): labs/fft/main.c src/fft.c src/config.c src/signal.c src/save.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| FFT                          | Done! |'

$(WINDOW): labs/window/main.c src/config.c src/window.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| WINDOW                       | Done! |'

$(CONV): labs/convolution/main.c src/config.c src/convolution.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| CONVOLITION                  | Done! |'

$(FIR): labs/fir/main.c src/fir.c src/signal.c src/dft.c src/convolution.c src/config.c src/window.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| FIR                          | Done! |'

$(IIR_1_ORDER): labs/iir-1-order/main.c src/signal.c src/config.c src/iir.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| IIR-1-ORDER                  | Done! |'
	
$(IIR_2_ORDER): labs/iir-2-order/main.c src/signal.c src/config.c src/iir.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| IIR-2-ORDER                  | Done! |'
	
$(IIR_2_ORDER_COMPLEX_POLE): labs/iir-2-order-complex-poles/main.c src/config.c src/iir.c src/complex.c src/save.c src/biquad.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| IIR-2-ORDER-COMPLEX-POLE     | Done! |'

$(IQ): labs/iq/main.c src/signal.c src/config.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| IQ                           | Done! |'

$(SHIFT): labs/shift/main.c src/signal.c src/config.c src/dft.c src/save.c src/shift.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| SHIFT                        | Done! |'

$(HILBERT): labs/hilbert/main.c src/signal.c src/config.c src/fir.c src/save.c src/convolution.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| HILBERT                      | Done! |'

$(DECIMATION): labs/decimation/main.c src/signal.c src/config.c src/save.c src/decimation.c src/dft.c src/convolution.c src/window.c src/fir.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| DECIMATION                   | Done! |'
	
$(INTERPOLATION): labs/interpolation/main.c src/signal.c src/config.c src/save.c src/interpolation.c src/dft.c src/fir.c src/window.c src/convolution.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| INTERPOLATION                | Done! |'
	
$(COHERENT_AVG): labs/coherent_avg/main.c src/signal.c src/config.c src/save.c src/noise.c src/stats.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| COHERENT_AVG                 | Done! |'
	
$(NON_COHERENT_AVG): labs/non_coherent_avg/main.c src/signal.c src/config.c src/save.c src/noise.c src/stats.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| NON_COHERENT_AVG             | Done! |'
	
$(SPECTRUM_SCALE): labs/spectrum_scale/main.c src/signal.c src/config.c src/save.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| SPECTRUM_SCALE               | Done! |'
	
$(MAG_APPROX): labs/magnitude_approximation/main.c src/signal.c src/config.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| MAGNITUDE APPROXIMATION      | Done! |'
	
$(COMPLEX_MUL): labs/complex_mul/main.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| COMPLEX MUL                  | Done! |'
	
$(RESTORE_SPECTRUM): labs/restore_spectrum/main.c src/signal.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| RESTORE SPECTRUM             | Done! |'
	
$(SPECTRUM_PEAK): labs/spectrum_peak/main.c src/signal.c src/config.c src/complex.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| SPECTRUM PEAK                | Done! |'
	
$(BIQUAD): labs/biquad/main.c src/biquad.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| BIQUAD                       | Done! |'
	
$(BUTTERWORTH): labs/butterworth/main.c src/biquad.c src/dft.c src/save.c src/sos.c src/signal.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| BUTTERWORTH                  | Done! |'
	
$(BUTTERWORTH_FLOAT_VS_DOUBLE): labs/butterworth-float-vs-double/main.c src/biquad.c src/dft.c src/save.c src/sos.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| BUTTERWORTH-FLOAT-VS-DOUBLE  | Done! |'
	
$(CHEBYSHEV_I): labs/chebyshev_I/main.c src/biquad.c src/dft.c src/save.c src/sos.c src/signal.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| CHEBYSHEV_I                  | Done! |'
	
$(CHEBYSHEV_II): labs/chebyshev_II/main.c src/biquad.c src/dft.c src/save.c src/sos.c src/signal.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| CHEBYSHEV_II                 | Done! |'
	
$(ELLIPTIC): labs/elliptic/main.c src/biquad.c src/dft.c src/save.c src/sos.c src/signal.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo '| ELLIPTIC                     | Done! |'

clean:
	@$(RM) $(OUTDIR)
	@echo 'Cleaning ... Done!'

help:
	@echo "Build a lab:"
	@echo "  make dft"
	@echo "  make fft"
	@echo "  make window"
	@echo "  make convolution"
	@echo "  make fir"
	@echo "  make iir_1_order"
	@echo "  make iir_2_order"
	@echo "  make iir_2_order_complex_pole"
	@echo "  make iq"
	@echo "  make shift"
	@echo "  make hilbert"
	@echo "  make decimation"
	@echo "  make interpolation"
	@echo "  make coherent_avg"
	@echo "  make non_coherent_avg"
	@echo "  make spectrum_scale"
	@echo "  make magnitude_approximation"
	@echo "  make complex_mul"
	@echo "  make restore_spectrum"
	@echo "  make spectrum_peak"
	@echo "  make biquad"
	@echo "  make butterworth"
	@echo "  make butterworth_float_vs_double"
	@echo "  make chebyshev_I"
	@echo "  make chebyshev_II"
	@echo "  make elliptic"
	@echo ""
	@echo "Build all labs:"
	@echo "  make all"
	@echo ""
	@echo "Clean generated binaries and data:"
	@echo "  make clean"
