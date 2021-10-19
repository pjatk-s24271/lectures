#include <iostream>
#include <string>

class ThisExample
{
  public:
    ThisExample() {
        
    }

    void printThis() {
        std::cout << this << '\n';
    }
};

int main(int argc, char *argv[])
{
    auto test = ThisExample();

    test.printThis();
    std::cout << &test << '\n';

    return 0;
}
