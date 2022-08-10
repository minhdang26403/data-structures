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
	stack_test \
	queue_test \
	hash_table_test \
	bst_test \
	heap_test \
	avl_test \
	sorting_test \
	red_black_tree_test \

all: $(PROGRAMS)

vector_test: $(TESTDIR)/vector_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

linked_list_test: $(TESTDIR)/linked_list_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

stack_test: $(TESTDIR)/stack_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

queue_test: $(TESTDIR)/queue_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

hash_table_test: $(TESTDIR)/hash_table_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

bst_test: $(TESTDIR)/bst_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

heap_test: $(TESTDIR)/heap_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

avl_test: $(TESTDIR)/avl_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

sorting_test: $(TESTDIR)/sorting_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

red_black_tree_test: $(TESTDIR)/red_black_tree_test.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.o *.a a.out *.err *~