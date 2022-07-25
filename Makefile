# Makefile
#****************************************************************

CC = gcc
CPP = g++
CFLAGS = -g -Wall -Wno-unused-function -std=c++11
LIBs = -lm
TESTDIR = ./test
INCLUDEDIR = -I./include -I.

PROGRAMS = vector_test

all: $(PROGRAMS)

vector_test: $(TESTDIR)/vector_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.o *.a