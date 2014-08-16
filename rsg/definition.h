#ifndef __DEFINITION_H__
#define __DEFINITION_H__

/**
 * Encapulates the data necessary to capture
 * the notion of a CFG Definition.  A Definition
 * is just a nonterminal paired with all of
 * its possible expansions.
 */

#include "production.h"
#include <vector>

using namespace std;  

class Definition {
  
 public:
  
  /**
   * Default Constructor: Definition
   * -------------------------------
   * Constructs an instance of the Defintion class
   * with the nonterminal string("") and an empty
   * collection of Productions.  This is supplied
   * for the purposes of embedding the Definition
   * in a vector or some other STL container that
   * requires its elements to have a default constructor.
   */
  
  Definition() {}
  
  /**
   * ifstream Constructor: Definition
   * --------------------------------
   * Constructs an instance of the Definition instance
   * based on the contents of the specified ifstream.
   *
   * @param infile a reference to the flat text grammar file being read.
   */
  
  Definition(ifstream& infile);

  /**
   * Method: getNonterminal
   * ----------------------
   * Returns a constant reference to the 
   * embedded nonterminal.
   *
   * @return an immutable reference to a string, which stores
   *         the nonterminal string.
   */
  
  const string& getNonterminal() const { return nonterminal; }
  
  /**
   * Method: getRandomProduction
   * ---------------------------
   * Returns an immutable reference to one and
   * exactly one of the Definition's expansions.
   * The Production is chosen at random.
   *
   * @return an immutable reference to a randomly selected
   *         Production held by the Definition.  It is assumed
   *         that the Definition has at least one Production.
   */
  
  const Production& getRandomProduction() const;
  
 private:
  string nonterminal;
  vector<Production> possibleExpansions;
};

#endif // __DEFINITION_H__
