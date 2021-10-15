#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::string pass = argv[1];
    std::string _pass;

    while(true) {
        std::cout << "password: ";
        std::getline(std::cin, _pass);
        if(_pass == pass) break;
    }

    std::cout << "ok!";
    return 0;
}
