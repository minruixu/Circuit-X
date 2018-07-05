cc = c++
CFLAGS = -Wall -lncurses -std=c++11 -I$(INCLUDES) -g

IDIR = ./includes/
SRCDIR = ./src/

INCLUDES = $(IDIR)

SOURCES = $(SRCDIR)*.cpp\

all:circuit

circuit:$(SOURCES)
	$(cc) $(SOURCES) $(CFLAGS) -o $@

run:
	./circuit

clean:
	rm circuit
