CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
CXX = g++
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -O2

STATIC_LIB = libhtab.a
SHARED_LIB = libhtab.so

LIB_FILES = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o

all: tail $(STATIC_LIB) $(SHARED_LIB) maxwordcount maxwordcount-dynamic maxwordcount-cpp

tail: tail.c

maxwordcount-cpp: maxwordcount-cpp.cc

maxwordcount: maxwordcount.o io.o $(STATIC_LIB)
	$(CC) $(CFLAGS) -static maxwordcount.o io.o -o $@ -L. -lhtab

maxwordcount-dynamic: maxwordcount.o io.o $(SHARED_LIB)
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ -L. -lhtab -Wl,-rpath,.

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(LIB_FILES)
	ar crs $@ $^

$(SHARED_LIB): $(LIB_FILES)
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

pack:
	zip xklyme00 *.c *.cc *.h Makefile

clean:
	rm -f *.o tail $(STATIC_LIB) $(SHARED_LIB) maxwordcount maxwordcount-dynamic maxwordcount-cpp