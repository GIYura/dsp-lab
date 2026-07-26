CC = gcc
RM = rm -rf

PLOT = gnuplot
SRCDIR = src
SCRIPT = scripts

STANDARD = -std=c99
OPTIMIZATION = -O0

CFLAGS = $(STANDARD) -g $(OPTIMIZATION) -Wall -Wpedantic -Wextra -MP -MMD
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
	
DEP = $(OBJ:.o=.d)
-include $(DEP)

clean:
	@$(RM) *.dat
	@$(RM) $(SRCDIR)/*.o $(SRCDIR)/*.d $(SRCDIR)/*.out $(SRCDIR)/*.s $(SRCDIR)/*.i
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'
	
help:
	@echo 'Run:'
	@echo '- make plot_in - display input signal'
	@echo '- make plot_spectrum - display spectrum'
	@echo '- make plot_window - display window function'
	@echo '- make plot_windowed - display windowed samples'
	@echo '- make plot_all - display all diagrams'
	@echo '- make - build project'
	@echo '- make clean - clean project'

run: $(TARGET)
	./$(TARGET)

plot_in: run
	$(PLOT) $(SCRIPT)/plot_in.gp
	
plot_window: run
	$(PLOT) $(SCRIPT)/plot_window.gp
	
plot_windowed: run
	$(PLOT) $(SCRIPT)/plot_windowed.gp
	
plot_spectrum: run
	$(PLOT) $(SCRIPT)/plot_spectrum.gp

plot_all: run
	$(PLOT) $(SCRIPT)/plot_all.gp
