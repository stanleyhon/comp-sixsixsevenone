#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H
#define _DEBUG_
#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;
template <typename T> class btree;
template <typename T> bool operator== (const btree_iterator<T>& left, const btree_iterator<T>& right);
template <typename T> bool operator!= (const btree_iterator<T>& left, const btree_iterator<T>& right);
template <typename T> bool operator== (const const_btree_iterator<T>& left, const const_btree_iterator<T>& right);
template <typename T> bool operator!= (const const_btree_iterator<T>& left, const const_btree_iterator<T>& right);

template <typename T>
class btree_iterator {
    public:

        friend class btree<T>;
        typedef ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        btree_iterator (node<T> * target, unsigned int data_index, const node<T> * root);
        friend bool operator==<T> (const btree_iterator<T>& left, const btree_iterator<T>& right);
        friend bool operator!=<T> (const btree_iterator<T>& left, const btree_iterator<T>& right);
        btree_iterator<T>& operator++ (); // prefix increment
        btree_iterator<T> operator++ (int); // postfix increment
        btree_iterator<T>& operator-- (); // prefix increment
        btree_iterator<T> operator-- (int); // postfix increment
        btree_iterator::pointer operator->();
        btree_iterator::reference operator* ();
    private:
        const node<T> * root_; // points to the root of this btree
        node<T> * target_; // which node does this iterator point at?
        unsigned int data_index_; // which element in this node does this iterator point at?
};

template <typename T>
class const_btree_iterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        const_btree_iterator (node<T> * target, unsigned int data_index, const node<T> * root);
        friend bool operator==<T> (const const_btree_iterator<T>& left, const const_btree_iterator<T>& right);
        friend bool operator!=<T> (const const_btree_iterator<T>& left, const const_btree_iterator<T>& right);
        const_btree_iterator<T>& operator++ (); // prefix increment
        const_btree_iterator<T> operator++ (int); // postfix increment
        const_btree_iterator<T>& operator-- (); // prefix increment
        const_btree_iterator<T> operator-- (int); // postfix increment
        const_btree_iterator::pointer operator->();
        const T& operator* ();
    private:
        const node<T> * root_; // points to the root of this btree
        node<T> * target_; // which node does this iterator point at?
        unsigned int data_index_; // which element in this node does this iterator point at?
};
#include "btree_iterator.tem"

#endif
