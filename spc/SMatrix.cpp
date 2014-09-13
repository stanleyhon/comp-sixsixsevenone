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

bool SMatrix::setVal(size_type row, size_type column, int value) throw(MatrixError) {
    // do bounds checking, throw MatrixError if wrong
    if (row > rows_ - 1 || column > columns_ - 1) {
        throw MatrixError ("Matrix bound error: (" + 
                std::to_string (row) + ", " + std::to_string (column) + ") entry of " + 
                std::to_string (rows_) + " x " + std::to_string (columns_) + " matrix\n");
    }

    // I don't think size errors can occur here

    if (value == 0) {
        return setValDelete (row, column, value);
    } else {
        return setValAdd (row, column, value);
    }
}

bool SMatrix::setValAdd (size_type row, size_type column, int value) {
    assert (value != 0);
    // See if we have any entries already on the row
    int newIndex = 0; // location where our new element should go in vals and cidx
    if (ridx_.find (row) == ridx_.end ()) { // nothing on the row, new row
        // insert the element into the map by reading closest previous row
        // value and using that +1 as hastable values
        int targetRow = row;
        while (targetRow != 0) {
            targetRow--;
            auto lookup = ridx_.find (targetRow);
            if (lookup != ridx_.end ()) { // found it!
                // Example:
                // ridx (2, 5) indicates 5 elements, starting from 2
                // therefor, we want to put ourselves at index 7
                newIndex = lookup->second.first + lookup->second.second;
                // Since this is a new row, we are guaranteed to only have
                // 1 non-zero element in the row
                ridx_[row] = std::make_pair (newIndex, 1);
                break;
            }

            // what if there's no rows before us?
            if (targetRow == 0) { // and we didn't find anything there. we're zero.
                ridx_[0] = std::make_pair (0, 1);
            }
        }

    } else {
        // modify the hashtable value to increase it's coverage range by 1
        auto lookup = ridx_.find (row);
        lookup->second.second++; // increment the coverage range by 1
        
        // figure out where it goes within that range, since cidx needs to stay
        // in sorted column order
        int idx = 0;
        newIndex = lookup->second.first;
        while (idx < lookup->second.second) { // check the cidx values within the range
            if (cidx_[newIndex + idx] < column) {
                idx++;
            } else { // we're smaller (i.e. we're in the right spot)
                newIndex += idx;
                break;
            }
        }
        // Check we're still within the range of our row
        assert (newIndex >= lookup->second.first); // above or at floor
        assert (newIndex < lookup->second.first + lookup->second.second); // below ceiling
    }
        
    // move all hashtable rows after this one range starts up by 1
    incrementRidx (row);

    // shift cidx up by 1
    // put in our value column
    insertCidx (newIndex, column);

    // shift vals up by 1
    // put in our value
    insertVals (newIndex, value);

    return true;
}
void SMatrix::incrementRidx (size_type insertionRow) {
    for (auto i = ridx_.begin (); i != ridx_.end (); ++i) {
        if (i->first > insertionRow) {
            i->second.first++; // need to shift this one up
        }
    }
    return;
}

bool SMatrix::insertCidx (int index, size_type column) {
    assert (index >= 0 && index <= cidxLength_);
    bool resized = false;
    // check if we need to expand array
    if (cidxLength_ == cidxSize_) { // need to resize array
        size_type * newCidx = new size_type[cidxSize_ * 2]; // double the array's size

        // copy the old info into the new one.
        memcpy (newCidx, cidx_, cidxLength_);

        // free the old one
        delete [] cidx_;

        // hook the new one up
        cidx_ = newCidx;

        // setup the info variables
        cidxSize_ = cidxSize_ * 2;

        resized = true;
    }

    assert (cidxLength_ + 1 <= cidxSize_);

    cidxLength_++; // there's going to be one more thing in the list now
    
    // example:
    // say we have 5 things, cidxLength_ would be 5
    // we need to insert a new one, so we increment cidxLength_ to 6
    // index 5 would be the "new" spot of memory
    // therefor use <
    for (int idx = index + 1; idx < cidxLength_; idx++) {
        cidx_[idx] = cidx_[idx - 1];
    }

    cidx_[index] = column; // put it in

    return resized;
} 

bool SMatrix::insertVals (int index, int value) {
    assert (index >= 0 && index <= valsLength_);
    bool resized = false;
    // check if we need to expand array
    if (valsLength_ == valsSize_) { // need to resize array
        int * newVals = new int[valsSize_ * 2]; // double the array's size

        // copy the old info into the new one.
        memcpy (newVals, vals_, valsLength_);

        // free the old one
        delete [] vals_;

        // hook the new one up
        vals_ = newVals;

        // setup the info variables
        valsSize_ = valsSize_ * 2;

        resized = true;
    }

    assert (valsLength_ + 1 <= valsSize_);

    valsLength_++; // there's going to be one more thing in the list now
    
    // example:
    // say we have 5 things, valsLength_ would be 5
    // we need to insert a new one, so we increment valsLength_ to 6
    // index 5 would be the "new" spot of memory
    // therefor use <
    for (int idx = index + 1; idx < valsLength_; idx++) {
        vals_[idx] = vals_[idx - 1];
    }

    vals_[index] = value; // put it in

    return resized;
} 

bool SMatrix::setValDelete (size_type row, size_type column, int value) {
    assert (value == 0);
    // no resize required for reduction
    // do a hastable lookup to figure out the range of which the value is at
    auto lookup = ridx_.find (row);
    if (lookup == ridx_.end ()) { // It was zero to begin with
        return false;
    }

    int startIndex = lookup->second.first; // the pair's left value, i.e. range start
    // the pair's right value, i.e. how many elements
    // need to subtract one, since starting at 3, and 3 elements = last valid element being 5
    int endIndex = startIndex + lookup->second.second - 1;
    std::cout << "startIndex is " + std::to_string (startIndex) << std::endl;
    std::cout << "endIndex is " + std::to_string (endIndex) << std::endl;
    int targetIndex = -1;
    while (startIndex <= endIndex) {
        std::cout << "cidx has " << cidx_[startIndex] << " at " << startIndex << std::endl;
        if (cidx_[startIndex] == column) { // found it
            targetIndex = startIndex;
            break;
        }
        startIndex++;
    }
    
    assert (targetIndex != -1);
    
    // fix up ridx
    // see if our entry needs removal entirely
    if (lookup->second.second == 1) { // there's only 1 thing in the row
        ridx_.erase (lookup);
    } else {
        lookup->second.second--; // otherwise just reduce it's range by 1
    }
    // now also reduce the start position of all latter rows
    for (auto i = ridx_.begin (); i != ridx_.end (); ++i) {
        if (i->first > row) {
            i->second.first--; // need to shift this range's start index down 1
        }
    }

    // fix up cidx;
    // example:
    // cidx array of length 6, means index 5 is the highest.
    // shifting elements left 1 means the final element does not get modified
    // just set it to 0, since in all cases of this function, the last element in the array
    // will be unset/zeroed
    assert (cidxLength_ != 0);
    for (int idx = targetIndex; idx < cidxLength_ - 1; idx++) {
        cidx_[idx] = cidx_[idx + 1];
    }

    // numerical to index so -1
    cidx_[cidxSize_ - 1] = 0;

    cidxLength_--;

    // fix up vals
    assert (valsLength_ != 0);
    for (int idx = targetIndex; idx < valsLength_ - 1; idx++) {
        vals_[idx] = vals_[idx + 1];
    }

    // numerical to index so -1
    vals_[valsSize_ - 1] = 0;

    valsLength_--;

    return false; 
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
