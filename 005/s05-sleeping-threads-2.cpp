#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>
#include <condition_variable>

std::mutex queue_mtx;
std::queue<std::string> queue;
std::condition_variable cv;

void print(int id)
{
    while(true) 
    {
        std::unique_lock < std::mutex > lock { queue_mtx };
        cv.wait(lock);

        std::string msg = queue.front();
        queue.pop();

        if(msg.empty()) break;
        
        std::cout << "from thread - " << id << ": " << msg << "\n";
    }

    std::cout << "thread " << id << " exiting\n";
}

//task unclear

int main() 
{
    std::thread t0(print, 111);
    std::thread t1(print, 222);
    std::thread t2(print, 333);
    std::thread t3(print, 444);
    
    t0.detach();
    t1.detach();
    t2.detach();
    t3.detach();

    int c = 0;
    std::string line;
    while(c < 4)
    {
        std::getline(std::cin, line);

        std::lock_guard <std::mutex> lock { queue_mtx };
        queue.push(line);
        cv.notify_one();

        if(line.empty()) c++;
    }
}