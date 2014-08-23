// ** DO NOT CHANGE THE CODE IN THIS FILE! **
// ** WE WILL USE OUR OWN VERSION DURING MARKING. **

#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <cassert> // for assert macro
#include "random.h"

/**
 * Constructor: RandomGenerator
 * ----------------------------
 * Initializes a RandomGenerator number generator, using 
 * informtaion based on the current time as the seed.
 * This is the traditional way to set the stage for a computer
 * program to use random numbers.
 */

RandomGenerator::RandomGenerator()
{
//  srand(time(NULL));
  srand(6771);
}

/**
 * Method: getRandomInteger
 * ------------------------
 * Returns a seemingly random number between
 * the specified low and high, inclusive.
 */

int RandomGenerator::getRandomInteger(int low, int high)
{
  assert(low <= high);
  double percent = (rand() / (static_cast<double>(RAND_MAX) + 1));
  assert(percent >= 0.0 && percent < 1.0); 
  int offset = static_cast<int>(percent * (high - low + 1));
  return low + offset;
}
