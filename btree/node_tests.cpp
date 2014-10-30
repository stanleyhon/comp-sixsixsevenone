#include "btree.h"
#include <ostream>
#include <cassert>


int main (void) {
    std::cout << "Testing node insertion and find functionality...\n";
    node<int> * root = new node<int> (4, nullptr, 0);
    root->insert (5);
    root->insert (10); // this wil move so the returned "iterator" will be invalid anyway
    root->insert (11);
    root->insert (6);
    root->insert (7);
    root->insert (8);
    
    root->insert (14);
    root->insert (9);
    root->insert (13);
    root->insert (15);

    assert (root != nullptr);
    node<int> * nullNode = static_cast<node<int>*> (nullptr);
    assert (root->find (5) != std::make_pair(nullNode, 0u));
    assert (root->find (10) != std::make_pair(nullNode, 0u));
    assert (root->find (11) != std::make_pair(nullNode, 0u));
    assert (root->find (6) != std::make_pair(nullNode, 0u));
    assert (root->find (7) != std::make_pair(nullNode, 0u));
    assert (root->find (8) != std::make_pair(nullNode, 0u));
    assert (root->find (14) != std::make_pair(nullNode, 0u));
    assert (root->find (9) != std::make_pair(nullNode, 0u));
    assert (root->find (13) != std::make_pair(nullNode, 0u));
    assert (root->find (15) != std::make_pair(nullNode, 0u));
    assert (root->find (115) == std::make_pair(nullNode, 0u));
    assert (root->find (-115) == std::make_pair(nullNode, 0u));
    assert (root->find (12) == std::make_pair(nullNode, 0u));
    std::cout << "PASS...\n";

    std::cout << "** Testing clone constructor\n";
    node<int> * newClone = new node<int> (*root, nullptr);
    assert (newClone != root);
    assert (newClone != nullptr);

    return 0;
}
