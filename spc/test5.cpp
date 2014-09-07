/**
Step 1. g++ -std=c++11 -Wall -Werror -O2 -o test5 Matrix.cpp test5.cpp
Step 2. ./test5 > test5.out
Step 3. diff test5.out test5.sol
**/

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix m   {{4,4,3}, {1,1,1}, {1,2,10}, {2,2,5}};

  std::cout << m << std::endl;

  return 0;
}
