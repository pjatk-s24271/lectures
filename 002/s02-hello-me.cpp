#include <iostream>
#include <string>

auto main() -> int
{
    std::string name;

    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "!\n";
    
    return 0;
}