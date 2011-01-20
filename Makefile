#ache; Cheng, Allan

CC = g++

all: sudsolve

sudsolve: sudsolve.o
	$(CC) -o sudsolve sudsolve.o

sudsolve.o: sudsolve.cpp
	$(CC) -o sudsolve.o -c sudsolve.cpp

clean:
	rm sudsolve sudsolve.o
