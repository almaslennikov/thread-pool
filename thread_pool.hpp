#pragma once

#include "task_thread.hpp"

#include <vector>
#include <future>

namespace t_pool
{
    class ThreadPool
    {
    public:
        explicit ThreadPool(size_t threadCount = 1);

        ~ThreadPool() = default;

        template<class Ret, class Fn, class... Args>
        std::future<Ret> runAsync(Fn function, Args... args)
        {
            auto promiseObj = std::make_shared<std::promise<Ret>>();

            getLeastBusyThread()->addTask([=]() {
                promiseObj->set_value(std::bind(function, args...)());
            });

            return promiseObj->get_future();
        };

    private:
        TaskThread::Ptr getLeastBusyThread();

        std::vector<TaskThread::Ptr> m_threads;
    };
}