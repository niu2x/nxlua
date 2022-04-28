#include "../pipe.h"

#include <string.h>

namespace nx::pipe::filter {

namespace {

static uint8_t hex_digit(uint8_t digit)
{
    if (digit < 10)
        return '0' + digit;
    return 'a' + digit - 10;
}

static uint8_t unhex_digit(uint8_t digit)
{
    if (digit <= '9')
        return digit - '0';

    if (digit <= 'F')
        return digit - 'A' + 10;

    return digit - 'a' + 10;
}

} // namespace

bool hex_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    (void)upstream_eof;
    uint8_t chr;
    while ((!rbuf.empty()) && (wbuf.user_capacity - wbuf.size() >= 2)) {
        rbuf.get(chr);
        wbuf.put(hex_digit(chr >> 4));
        wbuf.put(hex_digit(chr & 0xF));
    }
    return true;
}

unhex_t::unhex_t()
: size_(0)
{
}

bool unhex_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    (void)upstream_eof;
    while (!rbuf.empty() && !wbuf.full()) {

        while (size_ < 2 && !rbuf.empty()) {
            rbuf.get(buf_[size_++]);
        }

        if (size_ < 2)
            break;

        wbuf.put((unhex_digit(buf_[0]) << 4) | unhex_digit(buf_[1]));
        size_ = 0;
    }
    return true;
}

} // namespace nx::pipe::filter
