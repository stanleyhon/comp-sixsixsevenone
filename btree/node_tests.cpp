#include "btree.h"
#include <ostream>

#include <cassert>

int main (void) {
    std::cout << "Testing node insertion and find functionality...\n";
    node<int> * root = new node<int> (4);
    root->insert (5);
    root->insert (10);
    root->insert (11);
    root->insert (6);
    root->insert (7);
    root->insert (8);
    
    root->insert (14);
    root->insert (9);
    root->insert (13);
    root->insert (15);

    assert (root != nullptr);

    assert (root->find (5) == true);
    assert (root->find (10) == true);
    assert (root->find (11) == true);
    assert (root->find (6) == true);
    assert (root->find (7) == true);
    assert (root->find (8) == true);
    assert (root->find (14) == true);
    assert (root->find (9) == true);
    assert (root->find (13) == true);
    assert (root->find (15) == true);
    assert (root->find (115) == false);
    assert (root->find (-115) == false);
    assert (root->find (12) == false);
    std::cout << "PASS...\n";

    return 0;
}
