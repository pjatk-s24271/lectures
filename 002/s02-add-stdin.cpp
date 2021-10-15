#include <iostream>
#include <string>

int ask_user_for_integer(std::string output)
{
    std::string toReturn;

    std::cout << output;
    std::getline(std::cin, toReturn);

    return std::stoi(toReturn);
}

int main()
{
    int const a = ask_user_for_integer("a = ");
    int const b = ask_user_for_integer("b = ");

    std::cout << a << " + " << b << " = " << (a + b);
    return 0;
}