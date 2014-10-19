#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

template <typename T>
class btree_iterator {
    public:
        btree_iterator ();
    private:
        // things
        int x;
};

template <typename T>
class const_btree_iterator {
    public:
        const_btree_iterator ();
    private:
        // things
        int x;
};
#include "btree_iterator.tem"

#endif
