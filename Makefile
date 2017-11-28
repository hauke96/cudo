# Common definitions
CC = gcc

# Compiler flags, paths and libraries
CFLAGS = -std=c11 -pedantic -Wall -Wextra -ggdb
LFLAGS = $(CFLAGS)
LIBS   = -lm

TGTS = bin/cudo
OBJS = obj/cudo.o

# Targets...
all: cudo

cudo: $(OBJS) Makefile
	$(CC) $(LFLAGS) -o $(TGTS) $(OBJS) $(LIBS)

# Not necessary for this small build
# obj/cudo.o: src/cudo.c Makefile

# Rule to create *.o from *.c
obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) src/$*.c -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(TGTS)
