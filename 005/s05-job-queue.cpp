#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

std::mutex queue_mtx;
std::queue<int> queue;

void pullNumbers(int id)
{
    while(true) 
    {
        queue_mtx.lock();

        if(queue.empty())
        {
            queue_mtx.unlock();
            break;
        }

        int num = queue.front();
        queue.pop();

        std::cout << "from thread - " << id << ": " << num << "\n";

        queue_mtx.unlock();
    }
}

//task unclear

int main() 
{
    srand (time(NULL));

    for(int i = 0; i < 100; i++)
    {
        queue.push(rand() % 1000);
    }

    std::thread t0(pullNumbers, 111);
    std::thread t1(pullNumbers, 222);
    std::thread t2(pullNumbers, 333);
    
    t0.join();
    t1.join();
    t2.join();
}