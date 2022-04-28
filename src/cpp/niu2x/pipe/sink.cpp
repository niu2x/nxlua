#include <niu2x/pipe.h>

#include "pipe.h"

namespace nx::pipe {

sink_t::sink_t(std::ostream& stream)
: delegate_(&stream)
{
}

sink_t::~sink_t() { }

int sink_t::write(const void* data, size_t bytes)
{
    return std::visit(
        [data, bytes](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            return pipe::write(std::forward<T>(arg), data, bytes);
        },
        delegate_);
}

} // namespace nx::pipe