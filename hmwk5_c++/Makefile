#Makefile for graph library attempts

PROG = run
CC = g++
CPPFLAGS = -std=c++1z -fconcepts -Wall
OBJS = main.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp
# graph.o :
# 	$(CC) $(CPPFLAGS) -c graph.cpp
clean:
	rm -f core $(PROG) $(OBJS)