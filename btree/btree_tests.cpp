#include "btree.h"
#include <ostream>

#include <cassert>

int main (void) {
    btree<int> * newTree = new btree<int> (static_cast<size_t>(4));

    auto pair = std::make_pair (1, 2);
    if (pair == std::make_pair (3, 2)) {
        pair = std::make_pair (2, 3);
    }

    std::cout << "insert\n";
    newTree->insert (5);
    newTree->insert (1);
    newTree->insert (2);
    newTree->insert (4);
    newTree->insert (3);
    newTree->insert (9);
    newTree->insert (10);
    newTree->insert (11);
    newTree->insert (6);
    newTree->insert (7);
    newTree->insert (8);
    newTree->insert (12);
    newTree->insert (13);
    newTree->insert (14);

    std::cout << "ibegin\n";
    auto ibegin = newTree->begin();
    std::cout << "iend\n";
    auto iend = newTree->end();

    std::cout << "about to call ++\n";
    for (; ibegin != iend; ++ibegin) {
        std::cout << "DEREF: " << *ibegin << " \n";
    }
    (void) iend;
    return 0;
}

