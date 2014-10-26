/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>
#include <cassert>

#define _DEBUG_

template <typename T>
class btree_iterator;

// My class for handling btree nodes.
template <typename T>
class node {
    public:
        node (const unsigned int node_size, node<T> * parent, unsigned int child_index);
        ~node ();

        std::pair<btree_iterator<T>, bool> insert (const T& elem);
        std::pair<node<T> *, unsigned int> find (const T& elem);
        std::pair<node<T> *, unsigned int> next_node (void);
        std::pair<node<T> *, unsigned int> previous_node (void);
        
        const unsigned int node_size_;
        node<T>* parent_;
        
        // stores the value i, where we are the i-th child of the parent.
        const unsigned int child_index_; 
        const unsigned int max_children_;
        const unsigned int max_children_index_;
        
        std::vector<T> data_;
        node<T>** children_;
};

// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;
template <typename T> std::ostream& operator<< (std::ostream& os, const btree<T>& tree);

template <typename T> 
class btree {
    public:
        friend class btree_iterator<T>;
        friend class const_btree_iterator<T>;

        typedef btree_iterator<T> iterator;
        typedef const_btree_iterator<T> const_iterator;
        /** Hmm, need some iterator typedefs here... friends? **/

        /**
         * Constructs an empty btree.  Note that
         * the elements stored in your btree must
         * have a well-defined zero-arg constructor,
         * copy constructor, operator=, and destructor.
         * The elements must also know how to order themselves
         * relative to each other by implementing operator<
         * and operator==. (These are already implemented on
         * behalf of all built-ins: ints, doubles, strings, etc.)
         * 
         * @param maxNodeElems the maximum number of elements
         *        that can be stored in each B-Tree node
         */
        btree(size_t maxNodeElems = 40);

        /**
         * The copy constructor and  assignment operator.
         * They allow us to pass around B-Trees by value.
         * Although these operations are likely to be expensive
         * they make for an interesting programming exercise.
         * Implement these operations using value semantics and 
         * make sure they do not leak memory.
         */

        /** 
         * Copy constructor
         * Creates a new B-Tree as a copy of original.
         *
         * @param original a const lvalue reference to a B-Tree object
         */
        btree(const btree<T>& original);

        /** 
         * Move constructor
         * Creates a new B-Tree by "stealing" from original.
         *
         * @param original an rvalue reference to a B-Tree object
         */
        btree(btree<T>&& original);


        /** 
         * Copy assignment
         * Replaces the contents of this object with a copy of rhs.
         *
         * @param rhs a const lvalue reference to a B-Tree object
         */
        btree<T>& operator=(const btree<T>& rhs);

        /** 
         * Move assignment
         * Replaces the contents of this object with the "stolen"
         * contents of original.
         *
         * @param rhs a const reference to a B-Tree object
         */
        btree<T>& operator=(btree<T>&& rhs);

        /**
         * Puts a breadth-first traversal of the B-Tree onto the output
         * stream os. Elements must, in turn, support the output operator.
         * Elements are separated by space. Should not output any newlines.
         *
         * @param os a reference to a C++ output stream
         * @param tree a const reference to a B-Tree object
         * @return a reference to os
         */
        friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

        iterator begin (); 
        iterator end ();
        /**
         * The following can go here
         * -- begin() 
         * -- end() 
         * -- rbegin() 
         * -- rend() 
         * -- cbegin() 
         * -- cend() 
         * -- crbegin() 
         * -- crend() 
         */

        /**
         * Returns an iterator to the matching element, or whatever 
         * the non-const end() returns if the element could 
         * not be found.  
         *
         * @param elem the client element we are trying to match.  The elem,
         *        if an instance of a true class, relies on the operator< and
         *        and operator== methods to compare elem to elements already 
         *        in the btree.  You must ensure that your class implements
         *        these things, else code making use of btree<T>::find will
         *        not compile.
         * @return an iterator to the matching element, or whatever the
         *         non-const end() returns if no such match was ever found.
         */
        iterator find(const T& elem);

        /**
         * Identical in functionality to the non-const version of find, 
         * save the fact that what's pointed to by the returned iterator
         * is deemed as const and immutable.
         *
         * @param elem the client element we are trying to match.
         * @return an iterator to the matching element, or whatever the
         *         const end() returns if no such match was ever found.
         */
        const_iterator find(const T& elem) const;

        /**
         * Operation which inserts the specified element
         * into the btree if a matching element isn't already
         * present.  In the event where the element truly needs
         * to be inserted, the size of the btree is effectively
         * increases by one, and the pair that gets returned contains
         * an iterator to the inserted element and true in its first and
         * second fields.  
         *
         * If a matching element already exists in the btree, nothing
         * is added at all, and the size of the btree stays the same.  The 
         * returned pair still returns an iterator to the matching element, but
         * the second field of the returned pair will store false.  This
         * second value can be checked to after an insertion to decide whether
         * or not the btree got bigger.
         *
         * The insert method makes use of T's zero-arg constructor and 
         * operator= method, and if these things aren't available, 
         * then the call to btree<T>::insert will not compile.  The implementation
         * also makes use of the class's operator== and operator< as well.
         *
         * @param elem the element to be inserted.
         * @return a pair whose first field is an iterator positioned at
         *         the matching element in the btree, and whose second field 
         *         stores true if and only if the element needed to be added 
         *         because no matching element was there prior to the insert call.
         */
        std::pair<iterator, bool> insert(const T& elem);

        /**
         * Disposes of all internal resources, which includes
         * the disposal of any client objects previously
         * inserted using the insert operation. 
         * Check that your implementation does not leak memory!
         */
        ~btree();

    private:
        node <T> * root_;
        // The details of your implementation go here
};


    /**
     * The template implementation needs to be visible to whatever
     * translation unit makes use of templatized btree methods.
     * The unconventional practice is to #include the implementation
     * file just before the end of the interface (sort of like
     * sneaking it in and hoping it isn't noticed).  Because the
     * .tem file is included here, the .h file is NOT #included in 
     * the .tem file.  We'd otherwise have circular inclusions
     * and the compiler would be peeved.
     */

#include "btree.tem"

#endif
