CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2

all: tail

tail: tail.c

#write: write.c
#
#notepad: notepad.c

pack:
	zip xklyme00 *.c *.cc *.h Makefile

clean:
	rm -f *.o tail