#include <typeinfo>
#include <iostream>

int main () {
    const int val = 0;
    const auto& d = val;
    const int * ptr = &val;
    std::cout << d << std::endl;
    std::cout << typeid(d).name() << std::endl;

    return 0;
}
