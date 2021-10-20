#include <stdexcept>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace itp {
    struct timeout_expired_error : public std::runtime_error {
        using runtime_error::runtime_error;
    };

    template<typename T>
    struct channel {
        using queue_type = typename std::queue<T>;
        using value_type = typename queue_type::value_type;

        private:
            queue_type q;
            std::mutex m;
            std::condition_variable cv;

            auto pop() -> value_type
            {
                auto value = std::move(q.front());
                q.pop();
                return value;
            }

        public:
            auto wait() -> value_type
            {
                std::unique_lock<std::mutex> lck { m };
                if (not q.empty()) {
                    return pop();
                }

                cv.wait(lck, [this]{ return (not q.empty()); });
                return pop();
            }

            template<typename Rep, typename Period>
            auto wait_for(std::chrono::duration<Rep, Period> const duration) -> value_type
            {
                std::unique_lock<std::mutex> lck { m };
                if (not q.empty()) {
                    return pop();
                }

                cv.wait_for(lck, duration, [this]{ return (not q.empty()); });

                if (q.empty()) {
                    throw timeout_expired_error{"channel::wait_for()"};
                }

                return pop();
            }

            auto push(value_type const& value) -> void
            {
                {
                    std::lock_guard<std::mutex> lck { m };
                    q.push(value);
                }
                cv.notify_one();
            }

            auto push(value_type&& value) -> void
            {
                {
                    std::lock_guard<std::mutex> lck { m };
                    q.push(std::move(value));
                }
                cv.notify_one();
            }
    };
}

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>
#include <condition_variable>

itp::channel<std::string> queue;

void print(int id)
{
    while(true) 
    {
        std::string msg = queue.wait();
        
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
        queue.push(line);

        if(line.empty()) c++;
    }
}