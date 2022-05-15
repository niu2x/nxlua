#include "io_context.h"
#include "niu2x/log.h"

#include "thread_group.h"

namespace nxlua::thread {

io_context_t::io_context_t()
: closed_(false)
, keep_alive_(false)
{
}
io_context_t::~io_context_t() { printf("!io_context_t\n"); }

void io_context_t::post(task_t task)
{
    std::lock_guard<std::mutex> _(tasks_mutex_);
    if (closed_) {
        NX_LOG_E("io_context_t::post ignore task after closed");
        return;
    }
    tasks_.push_back(std::move(task));
    tasks_cv_.notify_one();
}

void io_context_t::run()
{
    std::unique_lock<std::mutex> lk(tasks_mutex_);
    while (true) {
        while (tasks_.size() > 0) {
            auto task = std::move(tasks_.front());
            tasks_.pop_front();
            lk.unlock();

            task();
            lk.lock();
        }

        if (keep_alive_ && (!closed_)) {
            tasks_cv_.wait(lk, [this] { return tasks_.size() > 0 || closed_; });
        } else {
            break;
        }
    }
}

void io_context_t::stop()
{
    std::lock_guard<std::mutex> _(tasks_mutex_);
    closed_ = true;
    tasks_cv_.notify_all();
}

void test()
{
    io_context_t context;
    context.post([] {
        for (int i = 0; i < 16; i++)
            printf("XXXXXXXXX\n");
    });
    context.post([] {
        for (int i = 0; i < 16; i++)
            printf("YYYYYYYYY\n");
    });

    thread_group_t tg;
    tg.add_thread(std::bind(&io_context_t::run, &context));
    tg.join_all();
}

} // namespace nxlua::thread