#include "pipe.h"

#include <iostream>

namespace nx::pipe {

template <>
int read(std::istream* device, void* data, size_t bytes)
{
    device->read(reinterpret_cast<char*>(data), bytes);
    if (device->good()) {
        return ok;
    } else if (device->eof()) {
        auto gcount = device->gcount();
        if (gcount > 0)
            return bytes - gcount;
        return -eof;
    } else {
        return -fail;
    }
}

template <>
int write(std::ostream* device, const void* data, size_t bytes)
{
    device->write(reinterpret_cast<const char*>(data), bytes);
    if (device->good()) {
        return ok;
    } else
        return -fail;
}

} // namespace nx::pipe