#include "../pipe.h"
#include <niu2x/log.h>
#include <string.h>

namespace nx::pipe::filter {

filter_t::filter_t()
: upstream_(nullptr)
, upstream_eof_(false)
, transform_eof_(false)
{
}

filter_t::~filter_t() { }

int filter_t::read(void* data, size_t bytes)
{
    if (transform_eof_ && wbuf_.empty())
        return -eof;

    rbuf_.normalize();
    wbuf_.normalize();

    read_from_upstream();

    transform_eof_ = transform_eof_
        || (transform(rbuf_, wbuf_, upstream_eof_) && upstream_eof_
            && rbuf_.empty());

    return write_to_downstream(data, bytes);
}

void filter_t::set_upstream(source_t p_upstream)
{
    upstream_ = std::move(p_upstream);
}

void filter_t::set_upstream(proxy_t p_upstream)
{
    upstream_ = std::move(p_upstream);
}

void filter_t::read_from_upstream()
{
    while (!rbuf_.full() && !upstream_eof_) {
        auto slots = rbuf_.continuous_slots();

        auto ret = std::visit(
            [&slots](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, nullptr_t>) {
                    return -eof;
                } else {
                    return arg.read(slots.base, slots.size);
                }
            },
            upstream_);

        if (ret >= 0) {
            rbuf_.update_size(slots.size - ret);
        } else if (ret == -eof) {
            upstream_eof_ = true;
        } else if (ret == -again) {

        } else
            return;
    }
}

int filter_t::write_to_downstream(void* p_data, size_t bytes)
{
    auto* data = reinterpret_cast<uint8_t*>(p_data);

    auto elems = wbuf_.continuous_elems();
    if (elems.size > 0 && bytes > 0) {
        auto writen = std::min(elems.size, bytes);
        memcpy(data, elems.base, writen);
        wbuf_.update_size(-writen);
        data += writen;
        bytes -= writen;
    }

    elems = wbuf_.continuous_elems();
    if (elems.size > 0 && bytes > 0) {
        auto writen = std::min(elems.size, bytes);
        memcpy(data, elems.base, writen);
        wbuf_.update_size(-writen);
        bytes -= writen;
    }

    return bytes;
}

filter_t::proxy_t operator|(
    filter_t::proxy_t p_source, filter_t::proxy_t p_filter)
{
    p_filter.set_upstream(p_source);
    return p_filter;
}

} // namespace nx::pipe::filter
