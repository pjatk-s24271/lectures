#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>
#include <condition_variable>

int num = 0;

std::mutex ping_mtx;
std::mutex pong_mtx;

std::condition_variable ping_cv;
std::condition_variable pong_cv;

void ping()
{
    while (true)
    {
        std::unique_lock < std::mutex > lock { ping_mtx };
        ping_cv.wait(lock);

        std::cout << "ping " << num << "\n";
        num += rand() % 42 + 1;
        
        pong_cv.notify_one();

        if(num > 1024) break;
    }
}

void pong()
{
    while (true)
    {
        std::unique_lock < std::mutex > lock { pong_mtx };
        pong_cv.wait(lock);

        std::cout << "pong " << num << "\n";
        num += rand() % 42 + 1;
        
        ping_cv.notify_one();

        if(num > 1024) break;
    }
}

//task unclear

int main()
{
    srand(time(NULL));

    std::thread _ping(ping);
    std::thread _pong(pong);

    _ping.detach();
    _pong.detach();

    usleep(1000);
    ping_cv.notify_one();

    while(num > 1024);
}