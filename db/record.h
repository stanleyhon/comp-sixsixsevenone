#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

#include "utility.h"

/* Database enums
 * --------------
 * Ideally, these enums would be declared inside the scope of
 * the Database class, but it turns out gcc doesn't not handle
 * nested enums inside a template class very well, so you will 
 * want to define that at the top-level scope as a workaround.
 */
 
enum DBSelectOperation { All, Clear, Add, Remove, Refine };
enum DBScope { AllRecords, SelectedRecords};
enum DBQueryOperator { Equal, NotEqual, LessThan, GreaterThan };

template <typename value> class Record;
template <typename value> ostream& operator<<(ostream& in, const Record<value>& r);
template <typename value> istream& operator>>(istream& in, Record<value>& r);

template <class value>
class Record {

  // Keep data as a map of 
  // strings 
  // TO 
  // std::vector <value>
  // This is so that we have fast access to a particular attribute
  // and all its values
  
  std::map <std::string, std::vector <value>> data_;

  // turns out we need to keep insertion order, so just 
  // keep a vector of strings to indicate what order to print in.
  std::vector <std::string> printOrder_;

  bool selected_; // keep track of our selected status

  friend ostream& operator<<<value>(ostream& out, const Record<value>& r);
  friend istream& operator>><value>(istream& in, Record<value>& r);
 
  public:
    Record (); // empty constructor
    ~Record (); // Destructor

    bool matchesQuery(const string& attr, DBQueryOperator op, 
            const value& want) const;

    // inlined simple selected functions
    bool isSelected () const { return selected_; };
    void setSelected (bool val) { selected_ = val; };

};

#include "record.tem"

#endif
