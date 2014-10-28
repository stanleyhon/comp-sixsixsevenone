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

    return 0;
}

