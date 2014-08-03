#include <iostream>

void swap3 (int & x, int & y,int & z);

int main (void) {
    int x, y, z;
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    int & xRef = x;
    int & yRef = y;
    int & zRef = z;

    swap3 (xRef, yRef, zRef);

    std::cout << xRef << std::endl;
    std::cout << yRef << std::endl;
    std::cout << zRef << std::endl;

    return 0;
}

void swap3 (int & x, int & y,int & z) {
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }

    if (y > z) {
        int temp = y;
        y = z;
        z = temp;
    }

    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
    
    return;
}


