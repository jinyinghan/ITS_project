OBJS = Test.o allosthread.o ThreadMutex.o

CC = g++

CFLAGS = -g -Wall -O 

Test:$(OBJS)
	$(CC) $(OBJS) -p -o Test -lpthread 
allosthread.o:allosthread.cpp allosthread.h
	$(CC) $(CFLAGS) -c allosthread.cpp
ThreadMutex.o:ThreadMutex.cpp ThreadMutex.h
	$(CC) $(CFLAGS) -c ThreadMutex.cpp
Test.o:Test.cpp allosthread.h ThreadMutex.h
	$(CC) $(CFLAGS) -c Test.cpp

clean:
	rm -rf *.o Test



