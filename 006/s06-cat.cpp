#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
    std::ifstream file(argv[1]);
    std::string line;

    if(argc != 2) {
        while(true) {
            std::getline(std::cin, line);
            std::cout << line << '\n';
        }
    }

    if(!file.good()) {
        std::cout << "cat: " << argv[1] << ": No such file or directory";
        return 0;
    }

    while(getline(file, line)) {
        std::cout << line;
        if(!file.eof()) std::cout << '\n';
    }

    return 0;
}
