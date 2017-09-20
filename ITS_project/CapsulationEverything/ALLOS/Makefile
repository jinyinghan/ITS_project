OBJS = Test.o allosthread.o ThreadMutex.o

CC = g++

CFLAGS = -Wall -O -g

test:$(OBJS)
	$(cc)$(OBJS) -p test -lpthread 
allosthread.o:allosthread.cpp allosthread.h
	$(cc)$(CFLAGS) -c allosthread.cpp
ThreadMutex.o:ThreadMutex.cpp ThreadMutex.h
	$(cc)$(CFLAGS) -c ThreadMutex.cpp
Test.o:Test.cpp allosthread.h ThreadMutex.h
	$(cc)$(CFLAGS) -c Test.cpp

clean:
	rm -rf *.o test



