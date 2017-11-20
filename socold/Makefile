OBJS = its.o CppSQLite3*.cpp allosthread.o #ThreadMutex.o Linklist.cpp 

CXX = g++

CXXFLAGS = -g -Wall -O 

itsc:$(OBJS)
	$(CXX) $(OBJS) -p -o itsc -lpthread -w -lsqlite3 -L/home/hanjinying/app/sqlite-snapshot-201710041413/.libs 
allosthread.o:allosthread.cpp 
	$(CXX) $(CXXFLAGS) -c allosthread.cpp
#ThreadMutex.o:ThreadMutex.cpp ThreadMutex.h
#	$(CXX) $(CXXFLAGS) -c ThreadMutex.cpp
#TLinklist.o:TLinklist.cpp TLinklist.h
#	$(CXX) $(CXXFLAGS) -c TLinklist.cpp
its.o:its.cpp 
	$(CXX) $(CXXFLAGS) -c its.cpp 

clean:
	rm -rf *.o *.out *.db itsc
