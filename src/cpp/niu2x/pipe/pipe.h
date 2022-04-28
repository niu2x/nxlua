#ifndef NX_SRC_PIPE_PIPE_H
#define NX_SRC_PIPE_PIPE_H

#include <niu2x/pipe.h>

#include <niu2x/utils.h>

namespace nx::pipe {

template <class Device>
int write(Device device, const void* data, size_t bytes);

template <class Device>
int read(Device device, void* data, size_t bytes);

template <>
int read(std::istream* device, void* data, size_t bytes);

template <>
int write(std::ostream* device, const void* data, size_t bytes);

}; // namespace nx::pipe

#endif