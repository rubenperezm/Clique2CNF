CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3 -w

EXES = main
OBJS = ${EXES:=.o}

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^

all: ${EXES}

run:
	./main

${OBJS}: reducer.hpp graph.hpp

clean:
	${RM} ${EXES} ${OBJS} subgraph*.txt *.cnf core *~
