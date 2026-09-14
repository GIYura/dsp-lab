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

.PHONY: all dft fft window convolution fir iir iq clean help

all: dft fft window convolution fir iir iq

dft: $(DFT)

fft: $(FFT)

window: $(WINDOW)

convolution: $(CONV)

fir: $(FIR)

iir: $(IIR)

iq: $(IQ)

$(OUTDIR):
	@mkdir -p $@

$(DFT): labs/dft/main.c src/dft.c src/config.c src/signal.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'DFT Done!'

$(FFT): labs/fft/main.c src/fft.c src/config.c src/signal.c src/output.c src/complex.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'FFT Done!'

$(WINDOW): labs/window/main.c src/config.c src/window.c src/signal.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'WINDOW Done!'

$(CONV): labs/convolution/main.c src/config.c src/convolution.c src/signal.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'CONV Done!'

$(FIR): labs/fir/main.c src/fir.c src/signal.c src/dft.c src/convolution.c src/config.c src/window.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'FIR Done!'

$(IIR): labs/iir/main.c src/signal.c src/config.c src/iir.c src/dft.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'IIR Done!'
	
$(IQ): labs/iq-vs-real/main.c src/signal.c src/config.c src/dft.c src/output.c | $(OUTDIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	@echo 'IQ Done!'

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
	@echo ""
	@echo "Build all labs:"
	@echo "  make all"
	@echo ""
	@echo "Clean generated binaries and data:"
	@echo "  make clean"
	