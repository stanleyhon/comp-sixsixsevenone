#include <iostream>

int main () {
    unsigned short a[] = {1, 2, 3, '\0'};
    unsigned short *p = a;

    while (*p) {
        std::cout << (*p)++ << std::endl;
    }

    int x = 0;
    while (x < 10) {
        std::cout << ++x;
    }

    return 0;
}
