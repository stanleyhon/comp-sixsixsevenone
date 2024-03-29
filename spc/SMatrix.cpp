#include "SMatrix.h"

// constructors
SMatrix::SMatrix(size_type size) : SMatrix (size, size) {} // the default constructor

// This constructor creates a zero matrix of
SMatrix::SMatrix(size_type rows, size_type columns) : valsLength_ (0), cidxLength_ (0),
                                                      rows_ (rows), columns_ (columns) {
    unsigned arraySize = std::min (static_cast<int>(rows * columns / 5), 1000);
    assert (arraySize == rows * columns / 5 || arraySize == 1000);

    if (arraySize == 0) {
        vals_ = nullptr;
        cidx_ = nullptr;
    } else {
        cidx_ = new size_type[arraySize];
        vals_ = new int[arraySize];
    }
    valsSize_ = arraySize;
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

void SMatrix::allocateArrays (unsigned rows, unsigned columns) {
    assert (rows >= 0 && columns >= 0);
    assert (vals_ == nullptr && cidx_ == nullptr);

    // Calculate and allocate vals and cidx arrays
    int arraySize = std::min ((rows * columns / 5), static_cast<unsigned>(1000));
    
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


SMatrix::SMatrix(const SMatrix& other) { // copy
    if (this != &other) {
        this->cidx_ = nullptr;
        this->cidxLength_ = 0;
        this->cidxSize_ = 0;
        this->vals_ = nullptr;
        this->valsLength_ = 0;
        this->valsSize_ = 0;
        this->rows_ = 0;
        this->columns_ = 0;
        *this = other; // copy operator
    }
}

SMatrix::SMatrix(SMatrix&& other) { // move
    if (*this != other) {
        *this = std::move(other);
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
    if (vals_ != nullptr) {
        delete [] vals_;
        vals_ = nullptr;
    }
    if (cidx_ != nullptr) {
        delete [] cidx_;
        cidx_ = nullptr;
    }
}

// operators
SMatrix& SMatrix::operator=(const SMatrix& other) { // copy
    if (this != &other) {
        // free our own resources
        // TODO: nullptr ok to free remove this
        if (vals_ != nullptr) {
            std::cout << "vals_ is " << vals_ << "\n\n";
            delete [] vals_;
        }
        if (cidx_ != nullptr) {
            delete [] cidx_;
        }

        // copy over the other stuff
        valsLength_ = other.valsLength_;
        vals_ = new int[other.valsSize_];
        valsSize_ = other.valsSize_;
        // TODO: reads unitialized! 
        std::copy (other.vals_, other.vals_ + other.valsSize_, vals_);

        cidxLength_ = other.cidxLength_;
        cidx_ = new size_type[other.cidxSize_];
        cidxSize_ = other.cidxSize_;
        std::copy (other.cidx_, other.cidx_ + other.cidxSize_, cidx_);

        ridx_ = other.ridx_; // copy implemented

        rows_ = other.rows_;
        columns_ = other.columns_;
    }
    return *this;
}

SMatrix& SMatrix::operator=(SMatrix&& other) { // move
    // move vals
    if (this != & other) {
        // free our own resources
        if (vals_ != nullptr) {
            delete [] vals_;
            vals_ = nullptr;
        }
        if (cidx_ != nullptr) {
            delete [] cidx_;
            cidx_ = nullptr;
        }
        ridx_ = other.ridx_; // copy is implemented for maps

        // steal other's
        vals_ = other.vals_;
        valsLength_ = other.valsLength_;
        cidx_ = other.cidx_;
        cidxLength_ = other.cidxLength_;
        ridx_ = other.ridx_;

        rows_ = other.rows_;
        columns_ = other.columns_;

        // set the other's size to 0x0
        other.rows_ = 0;
        other.columns_ = 0;
        other.vals_ = nullptr;
        other.cidx_ = nullptr;
    }

    return *this;
}

SMatrix& SMatrix::operator+=(const SMatrix& s) throw(MatrixError) {
    SMatrix sum = *this + s;
#ifdef DEBUG
    std::cout << "temporary sum successful\n";
#endif
    *this = std::move(sum);
    return *this;
}

SMatrix& SMatrix::operator-=(const SMatrix& s) throw(MatrixError) {
    *this = (*this - s);
    return *this;
}

SMatrix& SMatrix::operator*=(const SMatrix& s) throw(MatrixError) {
    *this = (*this * s);
    return *this;
}

int SMatrix::operator()(size_type s1, size_type s2) const throw(MatrixError) {
    if (s1 >= rows () || s2 >= cols ()) {
        throw MatrixError ("Matrix bound error: (" + 
                std::to_string (s1) + ", " + std::to_string (s2) + ") entry of " +
                std::to_string (rows ()) + " x " + std::to_string (cols ()) + " matrix\n");
    }

    // see if the row exists
    auto lookup = ridx_.find (s1);
    if (lookup == ridx_.end ()) {
        return 0;
    } else {
        int startIndex = lookup->second.first;
        unsigned idx = 0;
        // see if the column exists
        while (idx < lookup->second.second) {
            assert (startIndex + idx < cidxLength_);
            if (cidx_[startIndex + idx] == s2) { // found it!
                assert (vals_[startIndex + idx] != 0);
                return vals_[startIndex + idx];
            }            
            idx++;
        }
        std::cout << "RETURNING ZERO FROM END\n";
        return 0;
    }
}

bool SMatrix::setVal(size_type row, size_type column, int value) throw(MatrixError) {
    // do bounds checking, throw MatrixError if wrong
    if (row > rows_ - 1 || column > columns_ - 1) {
        throw MatrixError ("Matrix bound error: (" + 
                std::to_string (row) + ", " + std::to_string (column) + ") entry of " + 
                std::to_string (rows_) + " x " + std::to_string (columns_) + " matrix\n");
    }

    // I don't think size errors can occur here
#ifdef DEBUG
    std::cout << "setval called with " << row << " " << column << " " << value << std::endl;
#endif

    if (value == 0) {
        return setValDelete (row, column, value);
    } else {
        return setValAdd (row, column, value);
    }
}

bool SMatrix::setValAdd (size_type row, size_type column, int value) {
    assert (value != 0);
    
    // See if we have any entries already on the row
    unsigned newIndex = 0; // location where our new element should go in vals and cidx
    if (ridx_.find (row) == ridx_.end ()) { // nothing on the row, new row
#ifdef DEBUG
        std::cout << "setValAdd adding new row " << row << std::endl;
#endif
        // is our insertion row, the lowest row?
        auto firstRow = ridx_.begin();
        if (firstRow == ridx_.end() || firstRow->first > row) { // yes, we are the new lowest row
#ifdef DEBUG
            if (firstRow != ridx_.end ()) {
                std::cout << "Currently the lowest row is " << firstRow->first << std::endl;
            } else {
                std::cout << "Currently there are no entries in the ridx_ map" << std::endl;
            }
#endif
            assert (row < rows_);
            ridx_[row] = std::make_pair (0, 1);
        } else { // no, there are lower pairs
#ifdef DEBUG
            std::cout << "There are lower pairs. Looking for them now.\n" << std::endl;
#endif
            // find the closest lower pair
            // insert the element into the map by reading closest previous row
            // value and using that +1 as hastable values
            int targetRow = row;
            bool successful = false;
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
                    successful = true;
                    break;
                }
            }
            assert (successful == true);
            assert (targetRow >= 0);
        }
    } else { // existing row, there are nonzeros on this row
        // modify the hashtable value to increase it's coverage range by 1
        auto lookup = ridx_.find (row);
        assert (lookup != ridx_.end ());

        // see if it already exists, and just modify it then
        int cidxIndex = lookup->second.first;
        unsigned idx = 0;
        while (idx < lookup->second.second) {
            if (cidx_[cidxIndex + idx] == column) { // there's already an entry for it
                vals_[cidxIndex + idx] = value;
                return false;
            }
            idx++;
        }

        // It's a new entry, so we're gonna need extra range here
        lookup->second.second++; // increment the coverage range by 1
        
        // figure out where it goes within that range, since cidx needs to stay
        // in sorted column order
        newIndex = 0;
        unsigned rangeStart = lookup->second.first;
        // this should find us the first one larger than it.

        // TODO: when you shift arrays what happens if target index is at the end??
        size_type * b = cidx_ + rangeStart;
        size_type * e = cidx_ + rangeStart + lookup->second.second - 1;
        std::cout << "*** rangeStart: " << rangeStart << " *** lookup: " << e << "\n\n\n*****";
        assert (b <= cidx_ + cidxLength_);
        assert (e <= cidx_ + cidxLength_); // it's OK for e to be one past, since lower_bound never reads last
        assert (b >= cidx_ && e >= cidx_);
        size_type * found = std::lower_bound (b, e, column);
        if (found == e) { // goes at the end. i.e.
            newIndex = rangeStart + lookup->second.second - 1; // second.second is a range, so subtract one to count the first element
        } else {
            newIndex = found - cidx_;
            assert (newIndex < cidxLength_);
        }

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

bool SMatrix::insertCidx (unsigned index, size_type column) {
    assert (index >= 0 && index <= cidxLength_);
    bool resized = false;
    // check if we need to expand array
    if (cidxLength_ == cidxSize_) { // need to resize array
#ifdef DEBUG
        std::cout << "insertCidx is resizing!\n";
#endif
        // this fixes a bug where a matrix is initialized as 0 size
        // so the rule to double the size on limit reached does nothing
        if (cidxSize_ == 0) { 
            cidxSize_ = 1;
        }

        size_type * newCidx = new size_type[cidxSize_ * 2]; // double the array's size

        // copy the old info into the new one.
        if (cidx_ != nullptr) {
            std::copy (cidx_, cidx_ + cidxLength_, newCidx);
        }

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
    for (unsigned idx = index + 1; idx < cidxLength_; idx++) {
        cidx_[idx] = cidx_[idx - 1];
    }

    cidx_[index] = column; // put it in

    return resized;
} 

bool SMatrix::insertVals (unsigned index, int value) {
    assert (index >= 0 && index <= valsLength_);
    bool resized = false;
    // check if we need to expand array
    if (valsLength_ == valsSize_) { // need to resize array
        // this fixes a bug where a matrix is initialized as 0 size
        // so the rule to double the size on limit reached does nothing
        if (valsSize_ == 0) {
            valsSize_ = 1;
        }
        int * newVals = new int[valsSize_ * 2]; // double the array's size

        // copy the old info into the new one.
        std::copy (vals_, vals_ + valsLength_, newVals);

        // free the old one
        if (vals_ != nullptr) {
            delete [] vals_;
            vals_ = nullptr;
        }

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
    for (unsigned idx = index + 1; idx < valsLength_; idx++) {
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
    for (unsigned idx = targetIndex; idx < cidxLength_ - 1; idx++) {
        cidx_[idx] = cidx_[idx + 1];
    }

    // numerical to index so -1
    cidx_[cidxSize_ - 1] = 0;

    cidxLength_--;

    // fix up vals
    assert (valsLength_ != 0);
    for (unsigned idx = targetIndex; idx < valsLength_ - 1; idx++) {
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
        unsigned idx = 0;
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
bool operator==(const SMatrix& m1, const SMatrix& m2) {
    if (m1.cols () == 5) {
        std::cout << "HI";
    } else if (m1.rows () == 5) {
        std::cout << "hello";
    } else if (m2.cols () == 5) {
        std::cout << "rawr";
    } else if (m2.rows () == 5) {
        std::cout << "lel";
    }
    if (m1.rows () == m2.rows () && m1.cols () == m2.cols ()) {
        // check columns
        if (m1.cidxLength_ == m2.cidxLength_) {
            unsigned idx = 0;
            while (idx < m1.cidxLength_) {
                if (m1.cidx_[idx] != m2.cidx_[idx]) {
                    return false;
                }
                idx++;
            }
        } else {
            return false;
        }

        // check rows
        if (m1.ridx_.size () == m2.ridx_.size ()) {
            auto m1it = m1.ridx_.begin ();
            auto m2it = m2.ridx_.begin ();
            while (m1it != m1.ridx_.end () && m2it != m2.ridx_.end ()) {
                if (m1it->first != m2it->first) {
                    return false;
                }
                if (m1it->second.first != m2it->second.first) {
                    return false;
                }
                if (m1it->second.second != m2it->second.second) {
                    return false;
                }
                ++m1it;
                ++m2it;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
        
    return true;
}

bool operator!=(const SMatrix& s1, const SMatrix& s2) {
    return !(s1 == s2);
}

SMatrix operator+(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
    if (a.cols () != b.cols () || a.rows () != b.rows ()) {
        throw MatrixError ("Matrix size error: 9" + 
                std::to_string (a.rows ()) + " x " + std::to_string (a.cols ()) + ") + (" +
                std::to_string (b.rows ()) + " x " + std::to_string (b.cols ()) + ")\n");
    }

    SMatrix total (a);

    // iterate over all of b's values and add them to A
    for (auto row = b.ridx_.begin (); row != b.ridx_.end (); ++row) {
        unsigned idx = row->second.first; // start
        auto endIdx = idx + row->second.second; // count
        while (idx < endIdx) {
            int column = b.cidx_[idx];
            int value = b.vals_[idx];
            assert (value != 0);
            // add that to total's corresponding spot
            int oldValue = total (row->first, column);
            total.setVal (row->first, column, oldValue + value);
            idx++;
        }
    }

    return total;
}

SMatrix operator-(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
    if (a.cols () != b.cols () || a.rows () != b.rows ()) {
        throw MatrixError ("Matrix size error: 9" + 
                std::to_string (a.rows ()) + " x " + std::to_string (a.cols ()) + ") - (" +
                std::to_string (b.rows ()) + " x " + std::to_string (b.cols ()) + ")\n");
    }
    
    SMatrix total (a);
    
    // iterate over all of b's values and add them to A
    for (auto row = b.ridx_.begin (); row != b.ridx_.end (); ++row) {
        auto idx = row->second.first; // start
        auto endIdx = idx + row->second.second; // count
        while (idx < endIdx) {
            int column = b.cidx_[idx];
            int value = b.vals_[idx];
            assert (value != 0);
            // add that to total's corresponding spot
            int oldValue = total (row->first, column);
            total.setVal (row->first, column, oldValue - value);
            idx++;
        }
    }
    return total;
}

SMatrix operator*(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
    // Check sizes
    if (a.cols () != b.rows ()) {
        throw MatrixError ("Matrix size error: 9" + 
                std::to_string (a.rows ()) + " x " + std::to_string (a.cols ()) + ") * (" +
                std::to_string (b.rows ()) + " x " + std::to_string (b.cols ()) + ")\n");
    }

    // resulting matrix is of size a's row, b's cols
    SMatrix product (a.rows (), b.cols ());

    // figure out the columns which will actually need calculating
    // ie. the nonzero columns
    // remember them in a map
    // TODO: Amortise this by building it on insertions?
    std::map <SMatrix::size_type, SMatrix::size_type> validColumns;
    unsigned idx = 0;
    while (idx < a.cidxLength_) {
        validColumns[a.cidx_[idx]] = 1;
        idx++;
    }

    // for every valid row in A
    for (auto currentRow = a.ridx_.begin (); currentRow != a.ridx_.end (); ++currentRow) {
        // for every valid column in B
        for (auto currentCol = validColumns.begin (); currentCol != validColumns.end (); ++currentCol) {

            // calculate [currentRow, currentCol] for the product array
            // move across currentRow of a, and check all the valid [currentRow,col] combinations 
            // (use ridx_[currentRow] to get them
           
            // this is the start of the range of valid column values for currentRow
            auto aIdx = a.ridx_.find(currentRow->first)->second.first;
            unsigned int count = 0;
            auto total = 0;
            while (count < a.ridx_.find(currentRow->first)->second.second) { // only do the right number
                // use A's valid(nonzero) column, to see if we have a corresponding nonzero
                int bValue = b (a.cidx_[aIdx + count], currentCol->first);
                if (bValue != 0) {
                    total += a (currentRow->first, a.cidx_[aIdx + count]) * bValue;
                }
                count++;
            }
            if (total != 0) {
                product.setVal (currentRow->first, currentCol->first, total);
                total = 0;
            }
        }
    }
    return product;
}

SMatrix transpose(const SMatrix& a) {
    // the size is gonna be a.col, a.row
    SMatrix transposed (a.cols (), a.rows ()); // as opposed to a.row, a.col (see flipped!)

    // now iterate over all of the values, but put them in in a.col, a.row order
    for (auto row = a.ridx_.begin (); row != a.ridx_.end (); ++row) {
        auto index = row->second.first; // get the index where the data starts
        unsigned count = 0;
        while (count < row->second.second) {
            int column = a.cidx_[index + count];
            int value = a.vals_[index + count];
            // set the flipped version of it to tranposed
            transposed.setVal (column, row->first, value);
            count++;
        }
    }
    return transposed;
}

std::ostream& operator<<(std::ostream &os, const SMatrix &m) {
    if (m.rows() == 0 && m.cols() == 0) return os;

    assert (m.rows() != 0 && m.cols() != 0);

    // print (rows, columns, num-nonzero)\n
    os << "(" << m.rows() << "," << m.cols() << "," << m.valsLength_ << ")" << std::endl;

    // now print each row, in column order
    for (auto row = m.ridx_.begin (); row != m.ridx_.end (); ++row) {
        auto index = row->second.first; // get the index where the data starts
        unsigned count = 0;
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
    unsigned idx = 0;
    std::cout << "VALS: ";
    while (idx < valsLength_) {
        std::cout << vals_[idx] << " ";
        idx++;
    }
    std::cout << "\n";
    
    std::cout << "CIDX: ";
    for (auto i = ridx_.begin (); i != ridx_.end (); ++i) {
        unsigned innerIdx = i->second.first;
        std::cout << "*ROW " << i->first << " *: ";
        while (innerIdx < i->second.first + i->second.second) {
            std::cout << cidx_[innerIdx] << "[" << innerIdx << "] ";
            innerIdx++;
        }
        std::cout << "\n";
    }

    std::cout << "\n\n";

    return;
}
#endif

