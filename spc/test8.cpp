/**
Step 1. g++ -std=c++11 -Wall -Werror -O2 -o test5 Matrix.cpp test5.cpp
Step 2. ./test5 > test5.out
Step 3. diff test5.out test5.sol
**/

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix m   {{4,4,3}, {1,1,1}, {1,2,10}, {2,2,5}};
  const SMatrix mconst {{4,4,3}, {1,1,1}, {1,2,10}, {2,2,5}};

  for (m.begin (); !m.end (); m.next ()) {
      std::cout << m.value () << " ";
  }
  std::cout << std::endl;
  
  for (mconst.begin (); !mconst.end (); mconst.next ()) {
      std::cout << mconst.value () << " ";
  }
  std::cout << "\nfinished test8 iterator tests" <<  std::endl;

  // TEST PLUS

  SMatrix add1 {{2,2,2}, {0,0,1}, {0,1,1}};
  SMatrix add2 {{2,2,2}, {0,0,1}, {0,1,1}};

  std::cout << "add1" << add1 << std::endl;
  std::cout << "add2" << add2 << std::endl;
  std::cout << "ADD\n";
  std::cout << add1 + add2;
  std::cout << "SUBTRACT\n";
  std::cout << add1 - add2;
  
  SMatrix transposed = transpose (add1);

  std::cout << "transposed add1" << transposed << std::endl;

  std::cout << "\nfinished test8 add subtract transpose\n" << std::endl;

  std::cout << "add1 += add2: \n" << add1 << "\n" << add2 << "\n\n";
  add1 += add2;
  std::cout << "ANSWER: ";
  std::cout << add1;
  std::cout << "\n\n\n";
  
  std::cout << "add1 -= add2: \n" << add1 << "\n" << add2 << "\n\n";
  add1 -= add2;
  std::cout << "ANSWER: ";
  std::cout << add1;
  std::cout << "\n\n\n";

  std::cout << "add1 *= add2: \n" << add1 << "\n" << add2 << "\n\n";
  add1 *= add2;
  std::cout << "ANSWER: ";
  std::cout << add1;

  return 0;
}
