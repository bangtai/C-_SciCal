CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
MAIN = _main.cpp
MAINOBJ = $(MAIN:.cpp=.o)
MAINEXEC = $(MAIN:.cpp=)
VPATH = src:lib
SRCS = chol.cpp internal.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS2 = $(OBJS) generate_spd.o recover.o

all: $(MAINEXEC)

$(MAINEXEC): $(MAINOBJ) $(OBJS2)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(MAINOBJ): _internal_routines.h _chol.h _matrix_t.h

$(OBJS): _internal_routines.h _chol.h _matrix_t.h

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

test:
	rm -rf *.txt
	./$(MAINEXEC)

.PHONY: test

clean:
	rm -rf $(OBJS2) $(MAINOBJ) $(MAINEXEC) *.txt

.PHONY: clean
