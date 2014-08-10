#include <iostream>
#include <string>

int main (void) {
    std::string s ("wat ");

    for (auto i = s.begin (); i != s.end (); i++) {
        std::cout << *i << std::endl;
    }

    std::pair<std::string,int> p ("Months", 12);
    std::pair<std::string,int> p2 = {"Months", 12};
    std::pair<std::string,int> p3;
    p3 = std::make_pair ("months", 1412);

    std::cout << p.first << std::endl;
    std::cout << p.second << std::endl;
    
    std::cout << p2.first << std::endl;
    std::cout << p2.second << std::endl;
    
    std::cout << p3.first << std::endl;
    std::cout << p3.second << std::endl;

    return 0;
}
