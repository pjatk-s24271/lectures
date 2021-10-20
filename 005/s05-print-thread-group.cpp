#include <iostream>
#include <thread>

void print(int i, int ii)
{
    std::cout << "Hello, " << i << ii << "!\n";
}

//task unclear

int main() {
    std::thread threads[6];

    for(int i = 0; i < 7; i++)
    {
        for(int ii = 0; ii < 6; ii++)
        {
            threads[ii] = std::thread(print, i, ii);
        }

        for(int ii = 0; ii < 6; ii++)
        {
            threads[ii].join();
        }
    }
}