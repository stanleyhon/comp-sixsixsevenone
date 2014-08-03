#include <iostream>
#include <cmath>

int main (void) {
    double a, b, c;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    double s = (a + b + c) / 2;

    double result = sqrt (s * (s - a) * (s - b) * (s - c));

    std::cout << result << std::endl;

    return 0;
}


