#include <iostream>
#include <thread>
#include <chrono>
#include "thread_pool.hpp"

using namespace std::chrono_literals;

int main()
{
    const int TASK_COUNT = 16384;
    const int THREAD_COUNT = 64;

    t_pool::ThreadPool pool(THREAD_COUNT);
    std::vector<std::future<int>> v(TASK_COUNT);
    std::vector<int> result(TASK_COUNT);

    for(auto& it : v)
    {
        it = pool.runAsync<int>([](){
            int a = INT_MAX;
            int b = 0;
            while(a > 0)
            {
                b++;
                a -= b;
                a++;
            }
            return b;
        });
    }

    auto start = std::chrono::system_clock::now();
    for(int i = 0; i < TASK_COUNT; i++)
    {
        result[i] = v[i].get();
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << std::endl;


    return 0;
}