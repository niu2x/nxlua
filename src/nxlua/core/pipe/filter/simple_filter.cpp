#include "../pipe.h"

#include <string.h>

namespace nx::pipe::filter {

bool simple_filter_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    (void)upstream_eof;
    uint8_t chr;
    while (!rbuf.empty() && !wbuf.full()) {
        rbuf.get(chr);
        wbuf.put(transform(chr));
    }
    return true;
}

} // namespace nx::pipe::filter
