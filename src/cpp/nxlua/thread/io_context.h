#ifndef NXLUA_THREAD_IO_CONTEXT_H
#define NXLUA_THREAD_IO_CONTEXT_H

#include <functional>
#include <mutex>
#include <list>
#include <condition_variable>
#include <boost/noncopyable.hpp>

namespace nxlua::thread {

class io_context_t : private boost::noncopyable {
public:
    using task_t = std::function<void()>;

    io_context_t();
    ~io_context_t();

    io_context_t(io_context_t&&) = default;
    io_context_t& operator=(io_context_t&&) = default;

    void run();
    void stop();

    void post(task_t task);

    void set_keep_alive(bool b) { keep_alive_ = b; }

private:
    bool keep_alive_;

    std::list<task_t> tasks_;
    std::condition_variable tasks_cv_;
    std::mutex tasks_mutex_;
    bool closed_;
};

void test();

} // namespace nxlua::thread

#endif