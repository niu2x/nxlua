#include "thread_group.h"

#include <algorithm>
#include <sstream>

#include "niu2x/log.h"

namespace nxlua::thread {

thread_group_t::thread_group_t(){}
thread_group_t::~thread_group_t(){
	join_all();
}

void thread_group_t::_add_thread(std::thread && th) {
	std::stringstream os;
	os << th.get_id();
	{
		lock_t _(cls_mutex_);
		NX_LOG_D("thread_group_t::add_thread tid: %s", os.str().c_str());
		threads_.push_back(std::move(th));
	}
}

void thread_group_t::join_all() {
	std::decay_t<decltype(threads_)> threads;
	{
		lock_t _(cls_mutex_);
		 threads = std::move(threads_);
	}

	for(auto &th: threads) {
		if(th.joinable()){
			th.join();

			std::stringstream os;
			os << th.get_id();
			NX_LOG_D("thread_group_t::join_all join tid: %s", os.str().c_str());
		}
	}
}

void thread_group_t::_remove_thread(const std::thread::id &tid) {
	lock_t _(cls_mutex_);

	std::stringstream os;
	os << tid;
	NX_LOG_D("thread_group_t::_remove_thread tid: %s", os.str().c_str());

	auto it = std::find_if(
		threads_.begin()
		, threads_.end(), [&tid]( auto & v){
		return v.get_id() == tid;
	});

	if(it != threads_.end()) {
		it->detach();
		threads_.erase(it);
		NX_LOG_D("thread_group_t::_remove_thread detach tid: %s", os.str().c_str());
	}
}

void test(){
	thread_group_t tg;
	tg.add_thread([]{
	});

	tg.add_thread([]{
			
	});
	tg.join_all();
}

}