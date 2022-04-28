#include <niu2x/pipe.h>

#include "pipe.h"

namespace nx::pipe {

source_t::source_t(std::istream& stream)
: delegate_(&stream)
{
}

source_t::~source_t() { }

int source_t::read(void* data, size_t bytes)
{
    return std::visit(
        [data, bytes](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            return pipe::read(std::forward<T>(arg), data, bytes);
        },
        delegate_);
}

} // namespace nx::pipe