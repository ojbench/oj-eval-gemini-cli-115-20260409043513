CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

all: test_runner

test_runner: test.cpp src.hpp
	$(CXX) $(CXXFLAGS) test.cpp -o test_runner

test: test_runner
	./test_runner

clean:
	rm -f test_runner

.PHONY: all test clean
