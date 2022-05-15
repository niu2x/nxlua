#include "send.h"

#include "thread/thread_group.h"
#include "thread/io_context.h"

namespace nxlua::http {

class threadpool_t {
public:
    threadpool_t(int nproc)
    {
        io_context_.set_keep_alive(true);
        for (int i = 0; i < nproc; i++) {
            threadpool_.add_thread(std::bind(&threadpool_t::run, this));
        }
    }

    ~threadpool_t()
    {
        io_context_.stop();
        threadpool_.join_all();
    }

    void run() { io_context_.run(); }

    void post(thread::io_context_t::task_t task)
    {
        io_context_.post(std::move(task));
    }

private:
    thread::thread_group_t threadpool_;
    thread::io_context_t io_context_;
};

static threadpool_t* http_threadpool = nullptr;

void setup() { http_threadpool = new threadpool_t(2); }
void cleanup() { delete http_threadpool; }

void send(std::unique_ptr<request_t> request, send_callback_t&& callback)
{
    auto req = new std::unique_ptr<request_t>;
    *req = std::move(request);

    auto it = std::move([callback, req]() {
        auto response = (*req)->send();
        delete req;
        callback(std::move(response));
    });
    http_threadpool->post(std::move(it));
}

} // namespace nxlua::http