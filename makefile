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
IIR := $(OUTDIR)/iir_demo
IQ := $(OUTDIR)/iq_demo
SHIFT := $(OUTDIR)/shift_demo
HILBERT := $(OUTDIR)/hilbert_demo
DECIMATION := $(OUTDIR)/decimation_demo
INTERPOLATION := $(OUTDIR)/interpolation_demo
COHERENT_AVG := $(OUTDIR)/coherent_avg_demo
NON_COHERENT_AVG := $(OUTDIR)/non_coherent_avg_demo
SPECTRUM_SCALE := $(OUTDIR)/spectrum_scale_demo
MAG_APPROX := $(OUTDIR)/magnitude_approximation_demo

.PHONY: all dft fft window convolution fir iir iq shift hilbert decimation interpolation coherent_avg non_coherent_avg spectrum_scale magnitude_approximation clean help

all: dft fft window convolution fir iir iq shift hilbert decimation interpolation coherent_avg non_coherent_avg spectrum_scale magnitude_approximation

dft: $(DFT)

fft: $(FFT)

window: $(WINDOW)

convolution: $(CONV)

fir: $(FIR)

iir: $(IIR)

iq: $(IQ)

shift: $(SHIFT)

hilbert: $(HILBERT)

decimation: $(DECIMATION)

interpolation: $(INTERPOLATION)

coherent_avg: $(COHERENT_AVG)

non_coherent_avg: $(NON_COHERENT_AVG)

spectrum_scale: $(SPECTRUM_SCALE)

magnitude_approximation: $(MAG_APPROX)

$(OUTDIR):
	@mkdir -p $@

$(DFT): labs/dft/main.c src/dft.c src/config.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'DFT Done!'

$(FFT): labs/fft/main.c src/fft.c src/config.c src/signal.c src/save.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'FFT Done!'

$(WINDOW): labs/window/main.c src/config.c src/window.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'WINDOW Done!'

$(CONV): labs/convolution/main.c src/config.c src/convolution.c src/signal.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'CONV Done!'

$(FIR): labs/fir/main.c src/fir.c src/signal.c src/dft.c src/convolution.c src/config.c src/window.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'FIR Done!'

$(IIR): labs/iir/main.c src/signal.c src/config.c src/iir.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'IIR Done!'

$(IQ): labs/iq/main.c src/signal.c src/config.c src/dft.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'IQ Done!'

$(SHIFT): labs/shift/main.c src/signal.c src/config.c src/dft.c src/save.c src/shift.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'SHIFT Done!'

$(HILBERT): labs/hilbert/main.c src/signal.c src/config.c src/fir.c src/save.c src/convolution.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'HILBERT Done!'

$(DECIMATION): labs/decimation/main.c src/signal.c src/config.c src/save.c src/decimation.c src/dft.c src/convolution.c src/window.c src/fir.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'DECIMATION Done!'
	
$(INTERPOLATION): labs/interpolation/main.c src/signal.c src/config.c src/save.c src/interpolation.c src/dft.c src/fir.c src/window.c src/convolution.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'INTERPOLATION Done!'
	
$(COHERENT_AVG): labs/coherent_avg/main.c src/signal.c src/config.c src/save.c src/noise.c src/stats.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'COHERENT_AVG Done!'
	
$(NON_COHERENT_AVG): labs/non_coherent_avg/main.c src/signal.c src/config.c src/save.c src/noise.c src/stats.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'NON_COHERENT_AVG Done!'
	
$(SPECTRUM_SCALE): labs/spectrum_scale/main.c src/signal.c src/config.c src/save.c src/dft.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'SPECTRUM_SCALE Done!'
	
$(MAG_APPROX): labs/magnitude_approximation/main.c src/signal.c src/config.c src/save.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'MAGNITUDE APPROXIMATION Done!'

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
	@echo "  make iir"
	@echo "  make iq"
	@echo "  make shift"
	@echo "  make hilbert"
	@echo "  make decimation"
	@echo "  make interpolation"
	@echo "  make coherent_avg"
	@echo "  make non_coherent_avg"
	@echo "  make spectrum_scale"
	@echo "  make magnitude_approximation"
	@echo ""
	@echo "Build all labs:"
	@echo "  make all"
	@echo ""
	@echo "Clean generated binaries and data:"
	@echo "  make clean"
