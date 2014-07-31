#include <iostream>

int main () {
    int nums[] = {1, 2, 3, 4};
    const int *first = nums;
    const int *last = nums + 4;
    std::cout << first << std::endl;

    for (const int *ip = first ; ip != last; ip++) {
        std::cout << ip << std::endl;
        std::cout << *ip << std::endl;
    }
    return 0;
}
