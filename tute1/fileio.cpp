#include <iostream>
#include <fstream>
#include <fstream>

int main (void) {

    int i = 200;
    double d = 3.14159; // geddit?

    std::ofstream ofs ("output.txt", std::ofstream::out);

    ofs << i << std::endl;
    ofs << d << std::endl;

    ofs.close();

    std::ifstream ifs ("output.txt", std::ifstream::in);

    int readInteger;
    ifs >> readInteger;

    double readDouble;
    ifs >> readDouble;

    std::cout << "I read " << readInteger << " and " << readDouble << std::endl;

    ifs.close();

    return 0;
} 
