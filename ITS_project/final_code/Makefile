OBJS = itsc_main.o allosthread.o ThreadMutex.o CppSQLite3*.cpp Linklist.cpp 

CC = g++

CFLAGS = -g -Wall -O 

itsc:$(OBJS)
	$(CC) $(OBJS) -p -o itsc -lpthread -w -lsqlite3 -L/home/hanjinying/app/sqlite-snapshot-201710041413/.libs 
allosthread.o:allosthread.cpp allosthread.h
	$(CC) $(CFLAGS) -c allosthread.cpp
ThreadMutex.o:ThreadMutex.cpp ThreadMutex.h
	$(CC) $(CFLAGS) -c ThreadMutex.cpp
itsc_main.o:itsc_main.cpp allosthread.h ThreadMutex.h
	$(CC) $(CFLAGS) -c itsc_main.cpp

clean:
	rm -rf *.o *.out itsc
