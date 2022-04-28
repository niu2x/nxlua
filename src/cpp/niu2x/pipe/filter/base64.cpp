#include "../pipe.h"

#include <string.h>

extern "C" {
#include "base64/base64.h"
}

namespace nx::pipe::filter {

bool base64_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    size_t inlen;
    do {
        auto input = rbuf.continuous_elems();
        auto output = wbuf.continuous_slots();

        inlen = std::min(BASE64_DECODE_OUT_SIZE(output.size), input.size);

        if (!upstream_eof) {
            inlen = inlen / 3 * 3;
            if (inlen < 3) {
                break;
            }
        }

        auto outlen = base64_encode(
            (const unsigned char*)(input.base), inlen, (char*)(output.base));

        rbuf.update_size(-inlen);
        wbuf.update_size(outlen);
    } while (inlen > 0);
    return true;
}

bool unbase64_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    (void)upstream_eof;
    size_t inlen;
    do {
        auto input = rbuf.continuous_elems();
        auto output = wbuf.continuous_slots();

        inlen = std::min(BASE64_ENCODE_OUT_SIZE(output.size - 2), input.size);
        inlen = inlen & ~3;

        auto outlen = base64_decode(
            (const char*)(input.base), inlen, (unsigned char*)(output.base));

        rbuf.update_size(-inlen);
        wbuf.update_size(outlen);
    } while (inlen > 0);
    return true;
}

} // namespace nx::pipe::filter
