// #include "send.h"

// #include <boost/thread/thread.hpp>
// #include <boost/asio/io_context.hpp>
// #include <boost/asio/executor_work_guard.hpp>
// #include <boost/make_shared.hpp>

// namespace ba = boost::asio;

// namespace nxlua::http {

// class threadpool_t {
// public:
// 	threadpool_t(int nproc) {
// 		io_context_ = boost::make_shared<ba::io_context>();
// 		for(int i = 0; i < nproc; i ++){
// 			threadpool_.create_thread(boost::bind(&threadpool_t::run, this));
// 		}
// 	}

// 	~threadpool_t() {
// 		io_context_->stop();
// 		threadpool_.join_all();
// 	}

// 	void run(){
// 		auto work = ba::make_work_guard(*io_context_);
// 		io_context_->run();
// 	}
// private:
// 	boost::thread_group threadpool_;
// 	boost::shared_ptr<ba::io_context> io_context_;
// };

// static threadpool_t http_threadpool(2);

// void send(std::unique_ptr<request_t> request, send_callback_t callback) {

// }

// }