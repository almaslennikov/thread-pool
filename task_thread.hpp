#pragma once

#include <functional>
#include <thread>
#include <deque>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <future>

namespace t_pool
{
    using Task = std::function<void()>;

    class TaskThread final
    {
    public:
        using Ptr = std::shared_ptr<TaskThread>;

        TaskThread();
        ~TaskThread();

        size_t getTaskCount();
        void addTask(Task task);

    private:
        void execute();

        std::condition_variable m_conditionVariable;
        std::mutex m_mutex;
        std::thread m_thread;
        std::deque<Task> m_tasks;
        std::atomic<bool> m_isRunning;
    };
}
