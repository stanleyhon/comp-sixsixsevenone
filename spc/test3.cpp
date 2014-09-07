/**
 * On williams this test take about 0.2 secs when executed 
 * with my implementation, * which only uses straightforward
 * optimisations.
 *
 *
 * % uname -a
 % Linux wagner 2.6.38-2-amd64 #1 SMP Thu Apr 7 06:43:20 UTC 2011 x86_64 GNU/Linux
 * % time ./test3 > test3.sol
 * 
 * real	0m0.230s
 * user	0m0.092s
 * sys	0m0.016s
 */

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix a(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      a.setVal(i + 1000000, j + 1000000, -1);

  SMatrix b(1000000000, 500000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      b.setVal(i + 1000000, j + 1000000, -1);

  std::cout << a * b << std::endl;

  return 0;
}
