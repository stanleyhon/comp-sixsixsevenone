#include "btree.h"
#include <ostream>
#include <time.h>
#include <cassert>

int main (void) {
    btree<int> * newTree = new btree<int> (static_cast<size_t>(4));

    auto pair = std::make_pair (1, 2);
    if (pair == std::make_pair (3, 2)) {
        pair = std::make_pair (2, 3);
    }

    srand (time (NULL));

    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
    newTree->insert (rand() % 1000 + 1);
//    unsigned int val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
//    val = rand() % 100 + 1;
//    std::cout << "Inserting " << val << " \n";
//    newTree->insert (val);
    auto ibegin = newTree->begin();
    auto iend = newTree->end();

    auto savedIterator = ibegin;
    for (; ibegin != iend; ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
        savedIterator = ibegin; 
    }
    for (; savedIterator != newTree->begin(); savedIterator--) {
        std::cout << "DEREF BACKWARDS: " << *savedIterator << " \n";
    }
    std::cout << "DEREF BACKWARDS: " << *savedIterator << " \n";

    std::cout << "**** Testing << operator\n";
    btree<int> outputTree (4);
    outputTree.insert (5);
    outputTree.insert (6);
    outputTree.insert (7);
    outputTree.insert (8);
    outputTree.insert (1);
    outputTree.insert (2);
    outputTree.insert (3);
    outputTree.insert (4);
    outputTree.insert (9);
    outputTree.insert (10);
    outputTree.insert (11);
    outputTree.insert (12);
    std::cout << outputTree << "\n";

    std::cout <<"**** Testing move constructor\n";
    btree<int> moveConstructed (std::move(*newTree));
    for (ibegin = moveConstructed.begin(); ibegin != moveConstructed.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << moveConstructed << "\n";

    std::cout << "Printing out the moved guy: \n";
    std::cout << *newTree << "\n";
    delete newTree;

    std::cout << "**** Testing move assignment\n";
    btree<int> freshTree;
    freshTree = std::move (moveConstructed);
    
    for (ibegin = freshTree.begin(); ibegin != freshTree.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << freshTree << "\n";

    std::cout << "Printing out the moved guy: \n";
    std::cout << moveConstructed << "\n";
    
    std::cout << "**** Testing copy assignment\n";
    btree<int> copyassignment = freshTree;
    for (ibegin = freshTree.begin(); ibegin != freshTree.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << freshTree << "\n";
    for (ibegin = copyassignment.begin(); ibegin != copyassignment.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << copyassignment << "\n";

    btree<int> * gonnaDelete = new btree<int> (4);
    gonnaDelete->insert (6);
    gonnaDelete->insert (8);
    gonnaDelete->insert (13);
    gonnaDelete->insert (55);
    gonnaDelete->insert (5);
    gonnaDelete->insert (12);

    copyassignment = *gonnaDelete;
    delete gonnaDelete;
    for (ibegin = copyassignment.begin(); ibegin != copyassignment.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << copyassignment << "\n";

    std::cout << "**** Testing copy construction\n";
    gonnaDelete = new btree<int> (5);
    gonnaDelete->insert (31);
    gonnaDelete->insert (9);
    gonnaDelete->insert (34);
    gonnaDelete->insert (8);
    gonnaDelete->insert (52);
    gonnaDelete->insert (51);
    gonnaDelete->insert (3);

    btree<int> copyconstruction (*gonnaDelete);
    delete gonnaDelete;
    for (ibegin = copyconstruction.begin(); ibegin != copyconstruction.end(); ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    std::cout << copyconstruction << "\n";

    std::cout << "**** Testing reverse iterator\n";
    for (auto revIt = copyconstruction.rbegin(); revIt != copyconstruction.rend(); ++revIt) {
        std::cout << "DEREF: " << *revIt << " \n";
    }

    std::cout << "**** Testing const iterators\n";
    for (auto ci = copyconstruction.cbegin(); ci != copyconstruction.cend(); ++ci) {
        std::cout << "DEREF: " << *ci << " \n";
    }

    std::cout << "**** Testing const reverse iterator\n";
    for (auto cr = copyconstruction.crbegin(); cr != copyconstruction.crend(); ++cr) {
        auto test = cr;
        std::cout << "DEREF: " << *test << " \n";
    }

    std::cout << "**** Testing non-const find\n";
    auto location = copyconstruction.find (3);
    std::cout << "DEREF (3): " << *location << " \n";
    location = copyconstruction.find (555);
    assert (location == copyconstruction.end ());

    std::cout << "**** Testing const find\n";
    btree<int> anotherTree (5);
    anotherTree.insert (10);
    anotherTree.insert (62);
    anotherTree.insert (63);
    anotherTree.insert (18);
    anotherTree.insert (81);
    anotherTree.insert (61);
    anotherTree.insert (58);

    const btree<int> constTree = anotherTree;
    auto constLocation = constTree.find (18);
    std::cout << "DEREF (18): " << *constLocation << " \n";
    constLocation = constTree.find (60);
    assert (constLocation == constTree.cend());

    return 0;
}

