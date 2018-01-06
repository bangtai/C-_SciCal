
CXX = g++
CXXFLAGS = -Wall -g -std=c++1z
VPATH = solvers

#############################
# add linking libraries here
#############################
LIBS = -llapacke -lblas

#############################
# configure your main program
#############################
MAIN = main.cpp
EXEC = $(MAIN:.cpp=.out)
ARGS =


SRCS = LuSolver.cpp PpSolver.cpp TriSolver.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.h) BaseSolver.h poisson1d.h

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(OBJS)

.PHONY: all

test: $(EXEC)
	./$< $(ARGS)

.PHONY: test

clean:
	rm -rf $(OBJS) $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(MAIN) -o $@ $(LIBS)

$(OBJS): $(DEPS)
