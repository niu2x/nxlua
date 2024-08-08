#ifndef NX_EXCEPTION_H
#define NX_EXCEPTION_H

#include <exception>
#include <string>

namespace nx {

// exception
class exception : public std::exception {
public:
    exception(const char* msg, const char* file, uint32_t line)
    {
        snprintf(msg_, buffer_size, "%s\nat: %s line: %d", msg, file, line);
    }

    exception(const std::string& sz, const char* file, uint32_t line)
    : exception(sz.c_str(), file, line)
    {
    }

    virtual ~exception() { }
    virtual const char* what() const noexcept override { return msg_; }

private:
    // enum { buffer_size = limits::max_error_message };
    enum { buffer_size = 1024 };
    char msg_[buffer_size];
};

} // namespace nx

#define NX_THROW(message) throw nx::exception((message), __FILE__, __LINE__)

#endif