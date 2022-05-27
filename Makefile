CC=gcc
OPTS=-g -Wall -O3 -march=native
all:simulation
	
simulation: simulation.c
	$(CC) $(OPTS) simulation.c -o simulation -lm

.PHONY: clean
clean:
	rm -rf *.o simulation
