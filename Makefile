# Makefile
#****************************************************************

CC = gcc
CPP = g++
CFLAGS = -g -Wall -Wno-unused-function -std=c++11
LIBs = -lm
TESTDIR = ./test
INCLUDEDIR = -I./include -I.

PROGRAMS = vector_test \
	linked_list_test \
	sorting_test \
	stack_test

all: $(PROGRAMS)

vector_test: $(TESTDIR)/vector_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

linked_list_test: $(TESTDIR)/linked_list_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

stack_test: $(TESTDIR)/stack_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

queue_test: $(TESTDIR)/queue_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

sorting_test: $(TESTDIR)/sorting_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.o *.a a.out *.err *~