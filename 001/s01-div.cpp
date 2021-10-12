#include <iostream>

int main(int argc, char *argv[])
{
    int const a = std::stoi(argv[1]);
    int const b = std::stoi(argv[2]);
    
    std::cout << (a / b) << "\n";
    return 0;
}
