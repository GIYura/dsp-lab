CC = gcc
RM = rm -rf

PLOT = gnuplot
SRCDIR = src
SCRIPT = scripts

STANDARD = -std=c99
OPTIMIZATION = -O0

CFLAGS = $(STANDARD) -g $(OPTIMIZATION) -Wall -Wpedantic -MP -MMD
LDLIBS = -lm

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:.c=.o)
TARGET = dsp-lab

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $^ -o $@ $(LDLIBS)
	@echo 'Done!'

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
DEP := $(OBJ:.o=.d)
-include $(DEP)

clean:
	@$(RM) *.o *.d *.out *.s *.i *.dat
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'
	
help:
	@echo 'Run:'
	@echo '- make plot_in - display input signal'
	@echo '- make plot_sp - display spectrum'
	@echo '- make plot_win - display window function'
	@echo '- make plot_all - display all diagrams'
	@echo '- make - build project'
	@echo '- make clean - clean project'

debug:
	@echo $(SRC)

plot_in:
	$(PLOT) $(SCRIPT)/plot_in.gp
	
plot_win:
	$(PLOT) $(SCRIPT)/plot_window.gp
	
plot_sp:
	$(PLOT) $(SCRIPT)/plot_spectrum.gp

plot_all:
	$(PLOT) $(SCRIPT)/plot_all.gp
