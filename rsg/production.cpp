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
   // cout << "New production..." << endl;
   string nextToken;
   infile >> nextToken;
   while (nextToken.compare (";") != 0)
   {
      // cout << "Production adding " << nextToken << endl;
      phrases.push_back (nextToken);
      infile >> nextToken;
   }

   // read the new line after the semi-colon as well
   infile.get ();

   // cout << "End" << endl;
}
