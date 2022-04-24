# Makefile for Project 6
#****************************************************************

PROG = anglosaxon
CPPOPTIONS = -I../StanfordCPPLib -fvisibility-inlines-hidden -std=c++11 -g -Wall
LDOPTIONS = -L../StanfordCPPLib
LIB = -lStanfordCPPLib

all: test_list spl.jar

spl.jar:
	@ln -s ../StanfordCPPLib/spl.jar

test_list: test_list.o list.o
	g++ $(LDOPTIONS) -o test_list test_list.o list.o $(LIB)

test_list.o: test_list.cpp list.h
	g++ $(CPPOPTIONS) -c test_list.cpp

list.o: list.cpp list.h
	g++ $(CPPOPTIONS) -c list.cpp

$(PROG): $(PROG).o list.o
	g++ $(LDOPTIONS) -o $(PROG) $(PROG).o list.o $(LIB)

$(PROG).o: $(PROG).cpp list.h
	g++ $(CPPOPTIONS) -c $(PROG).cpp

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAMS)
