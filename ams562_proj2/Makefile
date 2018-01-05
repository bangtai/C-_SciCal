# Makefile
# implicit linking

CXX = g++
CXXFLAGS = -std=c++1z -g

TEST_FILE =

all:
	$(CXX) $(CXXFLAGS) main.cpp cvhull/GrahamScan.cpp -o myexec

test:
	./myexec $(TEST_FILE)

.PHONY: test

clean:
	rm -rf myexec

.PHONY: clean

cleanall:
	rm -rf myexec *.txt

.PHONY: cleanall
