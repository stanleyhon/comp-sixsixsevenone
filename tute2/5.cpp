#include <iostream>
#include <vector>

int main (void) {
    std::vector<int> v1(10, 1);
    std::vector<int> v2(5, 2);
    auto first = v1.cbegin ();
    v2.swap(v1);
    auto last = v2.cend();
    while (first != last) {
        std::cout << *first << std::endl;
        ++first;
    }

    return 0;
}
