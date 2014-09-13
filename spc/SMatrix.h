#ifndef SMATRIX_H
#define SMATRIX_H

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cstddef>


// matrix error class
class MatrixError : public std::exception {
 public:
  MatrixError(const std::string& what_arg) : _what(what_arg) { }
  virtual const char* what() const throw() { return _what.c_str (); }
  virtual ~MatrixError() throw() { }
 private:
  std::string _what;
};


// sparse matrix class
class SMatrix {
 public:
  // public interface
  // *** YOU SHOULD NOT MODIFY THE PUBLIC INTERFACE IN ANY WAY! ***

  // types
  typedef size_t size_type;

  // friends
  friend bool operator==(const SMatrix&, const SMatrix&);
  friend bool operator!=(const SMatrix&, const SMatrix&);
  friend SMatrix operator+(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator-(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator*(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix transpose(const SMatrix&);
  friend std::ostream& operator<<(std::ostream&, const SMatrix&);
  
  // constructors
  SMatrix(size_type size = 1); // the default constructor
  SMatrix(size_type, size_type);
  SMatrix(std::istream&);
  SMatrix(const SMatrix&);   // copy
  SMatrix(SMatrix&&);        // move
  SMatrix(const std::initializer_list<std::initializer_list<int>>&); // initializer_list

  // operators  
  SMatrix& operator=(const SMatrix&);  // copy 
  SMatrix& operator=(SMatrix&&);       // move
  SMatrix& operator+=(const SMatrix&) throw(MatrixError);
  SMatrix& operator-=(const SMatrix&) throw(MatrixError);
  SMatrix& operator*=(const SMatrix&) throw(MatrixError);
  int operator()(size_type, size_type) const throw(MatrixError);
  
  // operations
  inline size_type rows() const { return 5; };
  inline size_type cols() const { return 5; };
  bool setVal(size_type, size_type, int) throw(MatrixError);

  // `iterator' operations
  void begin() const;
  bool end() const;
  void next() const;
  int value() const;

  // destructor
  ~SMatrix();
  
  // static members  
  static SMatrix identity(size_type);

 private:
  // private data members
  int *vals_;
  int valsLength_; // holds how many things there are
  int valsSize_; // remembers how much we can store

  size_type *cidx_;
  int cidxLength_;
  int cidxSize_;

  std::map< size_type, std::pair<size_t, unsigned int> > ridx_;

  size_type rows_;
  size_type columns_;
  // you may/should augment the private interface as required by your implementation
 
  // PRIVATE HELPERS 
  // A helper used to allocate vals and cidx members to the required sizes.
  void allocateArrays (int rows, int columns);

  // Given a row where a new insertion was made, this function
  // iterates over higher rows and shifts their ranges up by 1
  // correcting ridx.
  void incrementRidx (size_type insertionRow);

  // Given a new non-zero value, row and column, shifts the cidx array up
  // and inserts the column in the correct position
  // Returns whether or not Cidx needed to be extended
  bool insertCidx (int index, int value);

  // Given an index of where the new value should go, shifts the vals array up
  // and inserts the value in the correct position
  // Returns whether or not not Vals needed to be extended
  bool insertVals (int index, int value);

  // Given an index of an element to be removed (or zeroed), shifts the array down
  void deleteVals (int index);

  // setVal delegates to this method when adding non-zero elements
  bool setValAdd (size_type row, size_type column, int value);

  // setVal delegates to this method when removing elements (i.e. adding zero elements)
  bool setValDelete (size_type row, size_type column, int value);

};

#endif
