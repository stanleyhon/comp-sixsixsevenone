// You should design a similar test case to test your
// copy and move assignment operators

#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m1(2, 3);

  for (SMatrix::size_type i = 0; i < 2; ++i)
    for (SMatrix::size_type j = 0; j < 3; ++j)
      m1.setVal(i, j, i+j);

  SMatrix m2 = m1;

  cout << "m1: " << endl << m1 << endl;
  cout << "m2: " << endl << m2 << endl;

  SMatrix m3 = move(m2);

  cout << "m1: " << endl << m1 << endl;
  cout << "m2: " << endl << m2 << endl;
  cout << "m3: " << endl << m3 << endl;

  return 0;
}
