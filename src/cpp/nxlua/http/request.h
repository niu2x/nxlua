#ifndef NXLUA_HTTP_REQUEST_H
#define NXLUA_HTTP_REQUEST_H

#include <string>
#include <curl/curl.h>

namespace nxlua::http {

class request_t {
public:
	request_t();
	~request_t();

	request_t(const request_t &)=default;
	request_t(request_t &&)=default;

	request_t& operator=(const request_t &)=default;
	request_t& operator=(request_t &&)=default;

private:
	std::string url_;
};

}

#endif