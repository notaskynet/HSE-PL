#pragma once

#include <functional>

#include <cstdint>

#include <vector>
#include <queue>

#include <future>
#include <atomic>
#include <thread>
#include <mutex>


class ThreadPool {
    std::atomic_bool is_done = false;
    uint32_t num_threads;

    std::vector<std::thread> threads;    
    std::queue<std::function<void()>> task_queue;
    std::mutex queue_mtx;

public:

    ThreadPool()
        : is_done{false} {
        num_threads = std::thread::hardware_concurrency();
        threads.reserve(num_threads);

        for (uint32_t i = 0; i < num_threads; ++i)  {
            threads.emplace_back(
                &ThreadPool::run, this
            );
        }

    }

    ThreadPool( uint32_t num_threads )
        : is_done{false}, num_threads(num_threads) {
        threads.reserve(num_threads);

        for (uint32_t i = 0; i < num_threads; ++i)  {
            threads.emplace_back(
                &ThreadPool::run, this
            );
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;

    ~ThreadPool() {
        is_done = true;

        for(uint32_t i = 0; i < threads.size(); ++i) {
            threads[i].join();
        }
    }

    template<class Function, class ...Args>
    auto add(Function function, Args&& ...args) noexcept
    -> std::future<std::result_of_t<Function(Args...)>>
    {
        using return_type = std::result_of_t<Function(Args...)>;

        std::lock_guard add_task_lg(queue_mtx);

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(
                std::forward<Function>(function),
                std::forward<Args>(args)...
            )
        );
        
        task_queue.emplace(
            [task]() -> void { (*task)(); }
        );
        return task->get_future();
    }

private:
    void run() noexcept {

        while(!is_done) {
            std::unique_lock<std::mutex> check_queue_ul(queue_mtx);

            if( !task_queue.empty() ) {
                auto task = std::move( task_queue.back() );
                task_queue.pop();
                check_queue_ul.unlock();
                task();
            }
        }
    }
};
