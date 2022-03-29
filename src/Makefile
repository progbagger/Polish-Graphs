CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFILES = cstack.c stack.c graph.c string_analysis.c
HEADERS = $(CFILES:.c=.h)
OBJECTS = $(CFILES:.c=.o)
EXEC = graph
PTH = ../build/
MAIN = main.c

all: build clean

build: $(EXEC)

$(EXEC): $(MAIN) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(PTH)$(EXEC) -lm

$(OBJECTS): $(CFILES)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o *.a *.out