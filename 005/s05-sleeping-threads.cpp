#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>

std::mutex queue_mtx;
std::queue<std::string> queue;

void print(int id)
{
    while(true) 
    {
        queue_mtx.lock();

        while (true)
        {
            if(queue.empty())
            {
                queue_mtx.unlock();
                break;
            }
        
            std::string msg = queue.front();
            queue.pop();

            if(msg.empty())
            {
                std::cout << "thread " << id << " exiting\n";
                queue_mtx.unlock();
                return;
            } 
            else 
            {
                std::cout << "from thread - " << id << ": " << msg << "\n";
            }
        }
        
        usleep(1000 * (rand() % 91 + 10));
    }
}

//task unclear

int main() 
{
    srand(time(NULL));

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
        queue.push(line);
        if(line.empty()) c++;
    }
}