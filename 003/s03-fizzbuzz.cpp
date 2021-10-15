#include <iostream>
#include <string>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    int num = std::stoi(argv[1]);
    bool fizz;
    bool buzz;

    for(int i = 0; i <= num; i++) {
        fizz = (i % 3) == 0;
        buzz = (i % 5) == 0;

        std::cout << i << "\n";

        if(fizz && buzz) {
            std::cout << "FizzBuzz\n";
        } else if(fizz) {
            std::cout << "Fizz\n";
        } else {
            std::cout << "Buzz\n";
        }
    }

    return 0;
}
