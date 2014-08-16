/**
 * Provides the implementation of the Production class, which
 * is simply a wrapper for the sequence of items (where items are terminals
 * or nonterminals).  It also completes the implementation of the ifstream
 * constructor, which was really the only thing missing from the .h
 */

#include "production.h"

/**
 * Constructor Implementation: Production
 * --------------------------------------
 * Constructor that initializes the Production based
 * on the content of a file.
 */

Production::Production(ifstream& infile)
{
#ifdef DEBUG
   cout << "New production..." << endl;
#endif
   string nextToken;
   infile >> nextToken;
   while (nextToken.compare (";") != 0)
   {
#ifdef DEBUG
      cout << "Production adding [" << nextToken << "]" << endl;
#endif
      phrases.push_back (nextToken);
      infile >> nextToken;
   }
#ifdef DEBUG
   cout << "End" << endl;
#endif
}
