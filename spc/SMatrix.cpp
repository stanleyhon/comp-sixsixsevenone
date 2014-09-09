#include "SMatrix.h"

// constructors
SMatrix::SMatrix(size_type size) : SMatrix (size, size) {} // the default constructor

// This constructor creates a zero matrix of
SMatrix::SMatrix(size_type rows, size_type columns) : valsLength_ (0), cidxLength_ (0),
                                                      rows_ (rows), columns_ (columns) {
    int arraySize = std::min (static_cast<int>(rows * columns / 5), 1000);
    assert (arraySize == rows * columns / 5 || arraySize == 1000);

    vals_ = new int[arraySize];
    valsSize_ = arraySize;

    cidx_ = new size_type[arraySize];
    cidxSize_ = arraySize;
}

#define MAX_THROWAWAY 5
SMatrix::SMatrix(std::istream& inputStream) {
    int rows, columns, nonZero;
    inputStream.ignore (MAX_THROWAWAY, '(');
    inputStream >> rows;
    inputStream.ignore (MAX_THROWAWAY, ','); // throw away characters up to a comma
    inputStream >> columns;
    inputStream.ignore (MAX_THROWAWAY, ',');
    inputStream >> nonZero;

    assert (rows >= 0 && columns >= 0 && nonZero >= 0);

    allocateArrays (rows, columns);

    // throw away stuff until we see a '(' or until we see EOF
    while (inputStream.ignore (MAX_THROWAWAY, '(').peek () != EOF) {
        int row, col, val;
        inputStream >> row;
        inputStream.ignore (MAX_THROWAWAY, ','); // throw away characters up to a comma
        inputStream >> col;
        inputStream.ignore (MAX_THROWAWAY, ',');
        inputStream >> val;

        // TODO: Insert ROW COL VAL i.e. setVal

    }
}

void SMatrix::allocateArrays (int rows, int columns) {
    assert (rows >= 0 && columns >= 0);
    assert (vals_ == nullptr && cidx_ == nullptr);

    // Calculate and allocate vals and cidx arrays
    int arraySize = std::min ((rows * columns / 5), 1000);
    
    vals_ = new int[arraySize];
    valsLength_ = 0;
    valsSize_ = arraySize;

    cidx_ = new size_type[arraySize];
    cidxLength_ = 0;
    cidxSize_ = arraySize;

    // Setup the rows_ columns_ members
    rows_ = rows;
    columns_ = columns;

    return;
}


SMatrix::SMatrix(const SMatrix& other) : vals_(other.vals_) { // copy
    if (*this != other) {
        // do stuff
    }
}

SMatrix::SMatrix(SMatrix&& other) : vals_(other.vals_) { // move
    if (*this != other) {
        // do stuff
    }
}

SMatrix::SMatrix(const std::initializer_list<std::initializer_list<int>>& il) { // initializer_list
    int rows, columns, nonZero;
    
    // iterate over each iterator list.
    for (auto i = il.begin (); i != il.end (); ++i) {
        // iterate over each item
        for (auto i2 = i->begin (); i2 != i->end (); ++i2) {
            if (i == il.begin ()) { // first items give us rows columns and nonzeros
                rows = *i2;
                ++i2;
                columns = *i2;
                ++i2;
                nonZero = *i2;

                allocateArrays (rows, columns);

                continue;
            } else { // the rest of them give us standard ROW/COL/VALs
                // TODO: hook this up to setVal
                int row = *i2;
                ++i2;
                int col = *i2;
                ++i2;
                int val = *i2;
                std::cout << row << col << val;
                continue;
            }
        }
    }
}

// destructor
SMatrix::~SMatrix() {
    delete [] vals_;
    delete [] cidx_;
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
