#include <iostream>
#include <vector>

int main (void) {
    std::vector<int> v(200, 0);
    std::vector<int>::iterator first = v.begin ();
    std::vector<int>::iterator last = v.end ();

    while (first != last) {
        ++first;
        first = v.insert (first, 42);
        last = v.end ();
        if (first + 1 != last) {
            ++first;
        } else {
            break;
        }
    }

    for (std::vector<int>::const_iterator i = v.begin (); i != v.end (); i++) {
        std::cout << *i << std::endl;
    }

    return 0;
}

