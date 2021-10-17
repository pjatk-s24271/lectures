#include <iostream>
#include <string>
#include <string.h>

int main(int argc, char *argv[])
{
    int num;
    if(argc == 2) {
        num = std::stoi(argv[1]);
    } else {
        num = 99;
    }

    while(true) {
        std::cout << num << " bottles of beer on the wall, " << num << " bottles of beer.\n";
        num--;
        std::cout << "Take one down, pass it around, " << num << " bottles of beer on the wall...\n\n";

        if(num == 2) break;
    }

    std::cout << "2 bottles of beer on the wall, 2 bottles of beer.\n";
    std::cout << "Take one down, pass it around, 1 bottle of beer on the wall...\n\n";

    std::cout << "1 bottle of beer on the wall, 1 bottle of beer.\n";
    std::cout << "Take one down, pass it around, no more bottles of beer on the wall.\n";

    std::cout << "Go to the store and buy some more, 99 bottles of beer on the wall...\n";

    return 0;
}
