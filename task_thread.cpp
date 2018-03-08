#include <iostream>
#include "task_thread.hpp"

namespace t_pool
{
    TaskThread::TaskThread() : m_isRunning(true),
                               m_thread(&TaskThread::execute, this)
    {}

    TaskThread::~TaskThread()
    {
        m_isRunning = false;
        m_conditionVariable.notify_one();
        m_thread.join();
    }

    size_t TaskThread::getTaskCount()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_tasks.size();
    };

    void TaskThread::addTask(Task task)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.push_back(task);
        m_conditionVariable.notify_one();
    }

    void TaskThread::execute()
    {
        while (m_isRunning)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_conditionVariable.wait(lock, [&]() {
                return !m_isRunning || !m_tasks.empty();
            });
            while (!m_tasks.empty())
            {
                auto taskToRun = m_tasks.front();
                lock.unlock();
                taskToRun();
                lock.lock();
                m_tasks.pop_front();
            }
        }
    }
}