#ifndef NXLUA_THREAD_THREAD_GROUP_H
#define NXLUA_THREAD_THREAD_GROUP_H

#include <thread>
#include <functional>
#include <mutex>
#include <list>
#include <boost/noncopyable.hpp>

namespace nxlua::thread {

class thread_group_t : private boost::noncopyable {
public:
    thread_group_t();
    ~thread_group_t();

    thread_group_t(thread_group_t&&) = default;
    thread_group_t& operator=(thread_group_t&&) = default;

    template <class Func, class... Args>
    void add_thread(Func&& func, Args&&... args)
    {
        _add_thread(std::thread([=]() {
            func(std::forward<Args>(args)...);
            _remove_thread(std::this_thread::get_id());
        }));
    }

    void join_all();

private:
    std::mutex cls_mutex_;
    using lock_t = std::lock_guard<std::mutex>;

    void _add_thread(std::thread&& th);
    void _remove_thread(const std::thread::id& tid);
    std::list<std::thread> threads_;
};
}

#endif