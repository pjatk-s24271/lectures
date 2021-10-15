#include <iostream>
#include <string>
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    srand (time(NULL));
    int random = rand() % 100;
    int guess = 0;
    std::string strGuess;

    while(true) {
        std::cout << "guess: ";
        std::getline(std::cin, strGuess);
        guess = std::stoi(strGuess);

        if(guess < random) {
            std::cout << "number too small!\n";
        } else if(guess > random) {
            std::cout << "number too big!\n";
        } else {
            std::cout << "just right!";
            break;
        }
    }

    return 0;
}
