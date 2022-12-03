CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3

EXES = main
OBJS = ${EXES:=.o}

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^

all: ${EXES}

run:
	./main

${OBJS}: reducer.hpp graph.hpp

clean:
	${RM} ${EXES} ${OBJS} core *~
