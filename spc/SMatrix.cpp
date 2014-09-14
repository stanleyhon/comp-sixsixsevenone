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
SMatrix::SMatrix(std::istream& inputStream) : vals_ (nullptr), cidx_ (nullptr) {
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

#ifdef DEBUG
        std::cout << row << " " << col << " " << val << std::endl;
#endif

        setVal (row, col, val);
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

SMatrix::SMatrix(const std::initializer_list<std::initializer_list<int>>& il) 
    : vals_ (nullptr), cidx_ (nullptr) { // initializer_list
    
    // iterate over each iterator list.
    for (auto i = il.begin (); i != il.end (); ++i) {
        // iterate over each item
        auto i2 = i->begin ();
        if (i == il.begin ()) { // first items give us rows columns and nonzeros
            int rows, columns, nonZero;
            rows = *i2;
            ++i2;
            columns = *i2;
            ++i2;
            nonZero = *i2;

#ifdef DEBUG
            std::cout << "rows: " << rows << " cols: " << columns 
                    << " nonZero: " << nonZero << std::endl;
#endif

            allocateArrays (rows, columns);
            std::cout << "finished" << std::endl;
            continue;
        } else { // the rest of them give us standard ROW/COL/VALs

            int row = *i2;
            ++i2;
            int col = *i2;
            ++i2;
            int val = *i2;
            
            setVal (row, col, val);
#ifdef DEBUG 
            std::cout << "row: " << row << " col: " << col << " val: " << val << std::endl;
#endif
            continue;
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
#ifdef DEBUG
        std::cout << "setValAdd adding new row " << row << std::endl;
#endif
        // is our insertion row, the lowest row?
        auto firstRow = ridx_.begin();
        if (firstRow == ridx_.end() || firstRow->first > row) { // yes, we are the new lowest row
#ifdef DEBUG
            std::cout << "Currently the lowest row is " << firstRow->first << std::endl;
#endif
            ridx_[row] = std::make_pair (0, 1);
        } else { // no, there are lower pairs
#ifdef DEBUG
            std::cout << "There are lower pairs. Looking for them now.\n" << std::endl;
#endif
            // find the closest lower pair
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
            }
            assert (targetRow >= 0);
        }
    } else {
#ifdef DEBUG
        std::cout << "setValAdd modifying old row\n";
#endif
        // modify the hashtable value to increase it's coverage range by 1
        auto lookup = ridx_.find (row);
        lookup->second.second++; // increment the coverage range by 1
        
        // figure out where it goes within that range, since cidx needs to stay
        // in sorted column order
        int idx = 0;
        newIndex = lookup->second.first;
        while (idx < lookup->second.second) { // check the cidx values within the range
            if (cidx_[newIndex + idx] < column) {
                newIndex++;
                idx++;
            } else { // we're smaller (i.e. we're in the right spot)
#ifdef DEBUG
                std::cout << "newIndex is " << newIndex << std::endl;
#endif         
                newIndex++;
                idx++;
                break;
            }
        }

        // the above loop always sets it to the correct index + 1
        newIndex--;

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
#ifdef DEBUG
        std::cout << "insertCidx is resizing!\n";
#endif
        size_type * newCidx = new size_type[cidxSize_ * 2]; // double the array's size

        // copy the old info into the new one.
        memcpy (newCidx, cidx_, cidxLength_ * sizeof (size_type));

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
        memcpy (newVals, vals_, valsLength_ * sizeof (int));

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
#ifdef DEBUG
        std::cout << "setValDelete found nothing in that row. Exiting\n";
#endif
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

#ifdef DEBUG
    debugPrintArrays ();
#endif
    // fix up vals
    assert (valsLength_ != 0);
    for (int idx = targetIndex; idx < valsLength_ - 1; idx++) {
        vals_[idx] = vals_[idx + 1];
    }

    // numerical to index so -1
    vals_[valsSize_ - 1] = 0;

#ifdef DEBUG
    std::cout << "setValDelete decrementing valsLength\n";
#endif

    valsLength_--;

    return false; 
}


void SMatrix::begin() const {
    iteratorRow_ = 0;
    iteratorCol_ = 0;
    return;
}

bool SMatrix::end() const {
    if (iteratorCol_ >= cols () || iteratorRow_ >= rows ()) { 
        return true; 
    } else { 
        return false;
    }
}

void SMatrix::next() const {
    if (iteratorCol_ == cols () - 1) { // it's already up to the last column
        iteratorCol_ = 0;
        iteratorRow_++;
    } else {
        iteratorCol_++;
    }
    return;
}

int SMatrix::value() const {
    assert (iteratorCol_ < cols () && iteratorRow_ < rows ());
    // see if the row exists
    auto lookup = ridx_.find (iteratorRow_);
    if (lookup == ridx_.end ()) {
        return 0;
    } else {
        int startIndex = lookup->second.first;
        int idx = 0;
        // see if the column exists
        while (idx < lookup->second.second) {
            if (cidx_[startIndex + idx] == iteratorCol_) { // found it!
                return vals_[startIndex + idx];
            } else {
                idx++;
            }
        }
        return 0;
    }
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
    if (m.rows() == 0 && m.cols() == 0) return os;

    assert (m.rows() != 0 && m.cols() != 0);

#ifdef DEBUG
    m.debugPrintArrays ();
#endif
    // print (rows, columns, num-nonzero)\n
    os << "(" << m.rows() << "," << m.cols() << "," << m.valsLength_ << ")" << std::endl;

    // now print each row, in column order
    for (auto row = m.ridx_.begin (); row != m.ridx_.end (); ++row) {
        int index = row->second.first; // get the index where the data starts
        int count = 0;
        while (count < row->second.second) { // read row->second.second many items
            // (ROW,COL,VAL)STD
            os << "(" << row->first << "," << m.cidx_[index + count] << "," 
                << m.vals_[index + count] << ")";
            count++;
            if (count < row->second.second) { //only put a space if there's going to be another
                os << " ";
            }
        }
        // see if there's more lines
        row++;
        if (row != m.ridx_.end ()) { // only print new line if there's more lines
            os << std::endl;
        }
        row--;
    }

    // this operator will be used as the primary testing mechanism
    // make sure that it behaves ***EXACTLY*** as specified

    return os;
}

#ifdef DEBUG
void SMatrix::debugPrintArrays (void) const {
    int idx = 0;
    std::cout << "VALS: ";
    while (idx < valsLength_) {
        std::cout << vals_[idx] << " ";
        idx++;
    }
    std::cout << "\n";
    
    idx = 0;
    std::cout << "CIDX: ";
    while (idx < cidxLength_) {
        std::cout << cidx_[idx] << " ";
        idx++;
    }
    std::cout << "\n\n";

    return;
}
#endif

