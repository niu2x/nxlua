#include "../pipe.h"

#include <string.h>

namespace nx::pipe::filter {

cut_t::cut_t(uint8_t chr)
: chr_(chr)
{
}

bool cut_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    (void)upstream_eof;
    uint8_t c;
    while ((!rbuf.empty()) && (!wbuf.full())) {
        rbuf.get(c);
        if (c != chr_)
            wbuf.put(c);
    }
    return true;
}

} // namespace nx::pipe::filter
