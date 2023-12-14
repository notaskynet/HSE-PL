#pragma once

#include <coroutine>
#include <cassert>


class Task {
public:
    struct promise_type {
        Task get_return_object() {
            return coro_handle::from_promise(*this);
        }

        auto initial_suspend() {
            return std::suspend_always();
        }
        
        auto final_suspend() noexcept {
            return std::suspend_always();
        }
        
        void return_void() {}
        
        void unhandled_exception() {
            std::terminate();
        }
    };
    using coro_handle = std::coroutine_handle<promise_type>;

    Task(coro_handle handle)
        : handle_(handle)
    { assert(handle); }

    ~Task() {
        handle_.destroy();
    }

    bool resume() {
        if(!handle_.done()) {
            handle_.resume();
        }
        return !handle_.done();
    }
private:
    coro_handle handle_;
};
