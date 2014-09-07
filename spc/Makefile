##
## Makefile for COMP3171/9171 Assignment 2: Sparse Matrix Class
##

# you may need to modify this line as necessary
CXX = g++
# enable this for Mac OS X or some CSE servers
#CXX = g++

# compiler flags
CPPFLAGS = -Wall -Werror -O2 -std=c++11
# enable this line for debugging
# CPPFLAGS = -Wall -g -std=c++11

default: test0 test1 test2 test3 test4 test5

test0: SMatrix.h SMatrix.cpp test0.cpp
	$(CXX) $(CPPFLAGS) -o test0 SMatrix.cpp test0.cpp

test1: SMatrix.h SMatrix.cpp test1.cpp
	$(CXX) $(CPPFLAGS) -o test1 SMatrix.cpp test1.cpp

test2: SMatrix.h SMatrix.cpp test2.cpp
	$(CXX) $(CPPFLAGS) -o test2 SMatrix.cpp test2.cpp

test3: SMatrix.h SMatrix.cpp test3.cpp
	$(CXX) $(CPPFLAGS) -o test3 SMatrix.cpp test3.cpp

test4: SMatrix.h SMatrix.cpp test4.cpp
	$(CXX) $(CPPFLAGS) -o test4 SMatrix.cpp test4.cpp

test5: SMatrix.h SMatrix.cpp test5.cpp
	$(CXX) $(CPPFLAGS) -o test5 SMatrix.cpp test5.cpp
clean: 
	rm -rf *.o a.out core *.dSYM test[0-4]

immaculate: clean
	rm -f test? *~
