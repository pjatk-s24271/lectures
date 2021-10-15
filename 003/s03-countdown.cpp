#include <iostream>

int main(int argc, char *argv[])
{
    int i = std::stoi(argv[1]);

    for(i; i >= 0; i--) {
        std::cout << i << "...\n";
    }

    return 0;
}
