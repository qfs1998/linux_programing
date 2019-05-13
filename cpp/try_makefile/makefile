CC = g++

CFLAGS = -lm -Wall -g

all: hello hi

hello: hello.cpp sayhello.o
	$(CC) $(CFLAGS) hello.cpp sayhello.o -o hello

hi: hi.cpp sayhi.o
	$(CC) $(CFLAGS) hi.cpp sayhi.o -o hi


sayhello.o: sayhello.cpp 
	$(CC) $(CFLAGS) -c sayhello.cpp
sayhi.o: sayhi.cpp 
	$(CC) $(CFLAGS) -c sayhi.cpp

clean:
	rm *.o hello hi
