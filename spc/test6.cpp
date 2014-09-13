
/**
Step 1. g++ -std=c++11 -Wall -Werror -O2 -o test0 Matrix.cpp test0.cpp
Step 2. ./test0 > test0.out
Step 3. diff test0.out test0.sol
**/

#include <iostream>
#include "SMatrix.h"

int main(void) {
    SMatrix m(5, 5);
    std::cout << "Constructed\n";
    m.setVal (0, 1, 5);
    std::cout << "set 0,1 to 5\n";
    m.setVal (1, 1, 6); 
    std::cout << "set 1,1 to 6\n";
    m.setVal (1, 1, 0);
    std::cout << "deleted 1,1 to 0\n";
    m.setVal (0, 1, 0);
    std::cout << "deleted 0,1 to 0\n";
    return 0;
}
