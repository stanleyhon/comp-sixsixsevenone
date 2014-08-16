#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

/**
 * Defines the abstraction for the Production class, 
 * which encapsulates the functionality needed to store
 * a contiguous list of strings.
 */
 
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Production {
  
 public:
  
  /**
   * Provides STL-like iterator access to the sequence of items making up
   * a Production instance.
   */
  
  typedef vector<string>::iterator iterator;
  typedef vector<string>::const_iterator const_iterator;
  
 public:
  
  /**
   * Default Constructor: Production
   * -------------------------------
   * Presented so that variables of type
   * Production may be declared without meaningful
   * initialization.
   * The primary reason this is here is that the 
   * vector class requires its element type to
   * have a default constructor.
   */
  
  Production() {}
  
  /**
   * ifstream Constructor: Production
   * --------------------------------
   * Initializes the Production based on the contents
   * of the specified ifstream.
   */
  
  Production(ifstream& infile);
  
  /**
   * vector<string>-backed Constructor: Production
   * ---------------------------------------------
   * Initializes a new Production to just encapsulate
   * a copy of the provided vector.
   */
  
  Production(const vector<string>& words) : phrases(words) {}
  
  /**
   * Iterators: begin, end
   * ---------------------
   * Returns an iterator (fancy word for the generalization
   * of a pointer) to the first element or the past-the-end 
   * element.  These iterators really are pointers to strings,
   * so they respond properly to the notion of increment and
   * dereference.
   * 
   * These functions are provided so that the Production
   * class, which is really just an ordered collection of
   * words, can be traversed via iterators.
   */
  
  iterator begin() { return phrases.begin(); }
  const_iterator begin() const { return phrases.begin(); }
  iterator end() { return phrases.end(); }
  const_iterator end() const { return phrases.end(); }
  
 private:
  vector<string> phrases;
};

#endif // __PRODUCTION_H__
