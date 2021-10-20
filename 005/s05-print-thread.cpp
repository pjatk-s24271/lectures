#include <iostream>
#include <thread>

void print(int i)
{
    std::cout << "Hello, " << i << "!\n";
}

//task unclear

int main() {
    for(int i = 0; i < 42; i++)
    {
        std::thread t(print, i);
        t.detach();
    }
}