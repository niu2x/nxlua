#ifndef NXLUA_HTTP_RESPONSE_H
#define NXLUA_HTTP_RESPONSE_H

#include <string>

namespace nxlua::http {

class response_t {
public:
    response_t();
    ~response_t();

    response_t(const response_t&) = default;
    response_t(response_t&&) = default;

    response_t& operator=(const response_t&) = default;
    response_t& operator=(response_t&&) = default;

    void set_http_code(int s) { http_code_ = s; }
    int http_code() const { return http_code_; }

    void set_curl_code(int s) { curl_code_ = s; }
    int curl_code() const { return curl_code_; }

    const std::string& body() const { return body_; }

    void set_body(std::string body) { body_ = std::move(body); }

private:
    int http_code_;
    int curl_code_;
    std::string body_;
};

}

#endif