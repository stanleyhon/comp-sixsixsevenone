/**
Step 1. g++ -std=c++11 -Wall -Werror -O2 -o test0 Matrix.cpp test0.cpp
Step 2. ./test0 > test0.out
Step 3. diff test0.out test0.sol
**/

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix m(std::cin);

  std::cout << m;

  return 0;
}
