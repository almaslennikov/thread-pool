#include "thread_pool.hpp"

#include <exception>
#include <memory>
#include <algorithm>
#include <c++/iostream>

namespace t_pool
{
    ThreadPool::ThreadPool(size_t threadCount)
    {
        if (threadCount < 1)
        {
            throw std::invalid_argument("Thread count cannot be less than 11");
        }

        for (size_t i = 0; i < threadCount; i++)
        {
            m_threads.push_back(std::make_shared<TaskThread>());
        }
    }

    TaskThread::Ptr ThreadPool::getLeastBusyThread()
    {
        return *std::min_element(m_threads.begin(),
                                 m_threads.end(),
                                 [](TaskThread::Ptr thread1, TaskThread::Ptr thread2) {
                                     return thread1->getTaskCount() < thread2->getTaskCount();
                                 });
    }
}