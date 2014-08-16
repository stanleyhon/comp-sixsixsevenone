/**
 * Provides the implementation of
 * the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal
 * attached to a string.
 */ 
 
#include "definition.h"
#include "random.h"
#include "assert.h"

/**
 * Constructor: Definition
 * -----------------------
 * Constructs an instance of a Definition object
 * based on the content of the specified file.
 */

Definition::Definition(ifstream& infile)
{
   string nextToken;
   infile >> nextToken;

   // throw away any junk before the open brace
   while (nextToken.compare ("{") != 0)
   {
      infile >> nextToken;
   }

   // The string after { is the nonterminal
   infile >> nextToken;
   // nextToken now contains this definition's title
   // save that
   nonterminal = nextToken;
   // cout << "Definition constructor called with nonterminal \n" << nonterminal << endl;

   // Now move on to start reading each production.
   bool finished = false;
   while (finished == false)
   {
      // each line is a "production"
      Production * p = new Production (infile);
      possibleExpansions.push_back (*p);
      
      // Check if there's a next line
      if (infile.peek () == '}') finished = true;
   }
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the
 * embedded Productions.
 */

const Production& Definition::getRandomProduction() const
{
   int low = 0;
   int high = possibleExpansions.size () - 1; // Convert from count to index.
   RandomGenerator rg;
   int returnIndex = rg.getRandomInteger (low, high);
   assert (returnIndex >= low && returnIndex <= high);

   return possibleExpansions.at (returnIndex);
}
