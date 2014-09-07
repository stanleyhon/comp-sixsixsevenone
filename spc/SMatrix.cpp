#include "SMatrix.h"

// constructors
SMatrix::SMatrix(size_type size) : vals_(nullptr) { // the default constructor
    // stuff;
}
    
SMatrix::SMatrix(size_type, size_type) : vals_(nullptr) {
    // stuff
}

SMatrix::SMatrix(std::istream&) : vals_(nullptr) {
    // stuff
}

SMatrix::SMatrix(const SMatrix& s) : vals_(s.vals_) { // copy
    // stuff
}

SMatrix::SMatrix(SMatrix&& s) : vals_(s.vals_) { // move
    // stuff
}

SMatrix::SMatrix(const std::initializer_list<std::initializer_list<int>>& a) : vals_(nullptr) { // initializer_list
    // stuff
}

// destructor
SMatrix::~SMatrix() {
    delete vals_;
}

// operators  
SMatrix& SMatrix::operator=(const SMatrix& s) { // copy
    SMatrix * s2 = new SMatrix (1);
    return *s2;
}
   
SMatrix& SMatrix::operator=(SMatrix&& s) { // move
    return s;
}

SMatrix& SMatrix::operator+=(const SMatrix& s) throw(MatrixError) {
    SMatrix * s2 = new SMatrix (1);
    return *s2;
}

SMatrix& SMatrix::operator-=(const SMatrix& s) throw(MatrixError) {
    SMatrix * s2 = new SMatrix (1);
    return *s2;
}

SMatrix& SMatrix::operator*=(const SMatrix& s) throw(MatrixError) {
    SMatrix * s2 = new SMatrix (1);
    return *s2;
}

int SMatrix::operator()(size_type s1, size_type s2) const throw(MatrixError) {
    return s1;
}

bool SMatrix::setVal(size_type, size_type, int) throw(MatrixError) {
    return true;
}

void SMatrix::begin() const {
    return;
}

bool SMatrix::end() const {
    return true;
}

void SMatrix::next() const {
    return;
}

int SMatrix::value() const {
    return 5;
}

// friends
bool operator==(const SMatrix&, const SMatrix&) {
    return true;
}

bool operator!=(const SMatrix&, const SMatrix&) {
    return false;
}

SMatrix operator+(const SMatrix&, const SMatrix&) throw(MatrixError) {
    return SMatrix(1);
} 

SMatrix operator-(const SMatrix&, const SMatrix&) throw(MatrixError) {
    return SMatrix(1);
} 

SMatrix operator*(const SMatrix&, const SMatrix&) throw(MatrixError) {
    return SMatrix(1);
}

SMatrix transpose(const SMatrix&) {
    return SMatrix(1);
}

std::ostream& operator<<(std::ostream &os, const SMatrix &m) {

  // this operator will be used as the primary testing mechanism
  // make sure that it behaves ***EXACTLY*** as specified

  return os;
}
