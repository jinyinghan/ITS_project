#Makefile

PROGS =main
CLEANFILES = core core.* *.core *.o temp.* *.out typescript* \
        *.lc *.lh *.bsdi *.sparc *.uw

all :${PROGS}


CXXFLAGS+=-g  -std=c++11

main: main.o Thread.o MutexLock.o Condition.o
	${CXX} ${CXXFLAGS} -o $@ $^ -lpthread
clean:
	rm -f ${PROGS} ${CLEANFILES}
