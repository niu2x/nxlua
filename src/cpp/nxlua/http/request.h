#ifndef NXLUA_HTTP_REQUEST_H
#define NXLUA_HTTP_REQUEST_H

#include <string>
#include <memory>
#include <curl/curl.h>

#include "response.h"

namespace nxlua::http {

class request_t {
public:
	request_t();
	~request_t();

	request_t(const request_t &)=default;
	request_t(request_t &&)=default;

	request_t& operator=(const request_t &)=default;
	request_t& operator=(request_t &&)=default;

    std::unique_ptr<response_t> send();

    void set_url(std::string url) { url_ = std::move(url); }

private:
	std::string url_;
};

}

#endif