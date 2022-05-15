#ifndef NXLUA_HTTP_REQUEST_H
#define NXLUA_HTTP_REQUEST_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <curl/curl.h>

#include "response.h"

namespace nxlua::http {

enum method_t {
    GET,
    POST,
    PUT,
};

class request_t {
public:
    enum {};

    request_t();
    ~request_t();

	request_t(const request_t &)=default;
	request_t(request_t &&)=default;

	request_t& operator=(const request_t &)=default;
	request_t& operator=(request_t &&)=default;

    std::unique_ptr<response_t> send();

    void set_url(std::string url) { url_ = std::move(url); }
    void set_method(method_t m) { method_ = m; }

    void set_header(const std::string& key, std::string value);

private:
	std::string url_;
    method_t method_;
    std::map<std::string, std::string> header_;
};

}

#endif