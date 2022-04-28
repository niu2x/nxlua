#include <niu2x/pipe.h>
#include <niu2x/log.h>
#include <niu2x/ringbuf.h>

#include <niu2x/utils.h>

namespace nx::pipe {

bool operator|(source_t p_source, sink_t p_sink)
{
    filter::ringbuf buf;

    bool source_eof = false;

    do {
        while ((!buf.full()) && (!source_eof)) {
            auto slots = buf.continuous_slots();
            auto ret = p_source.read(slots.base, slots.size);

            if (ret >= 0) {
                buf.update_size(slots.size - ret);
            } else if (ret == -eof) {
                source_eof = true;
            } else if (ret == -again) {

            } else
                return false;
        }

        while (!buf.empty()) {
            auto elems = buf.continuous_elems();
            auto ret = p_sink.write(elems.base, elems.size);

            if (ret >= 0) {
                buf.update_size(-(elems.size - ret));
            } else if (ret == -again) {

            } else
                return false;
        }

    } while ((!source_eof) || (!buf.empty()));

    return true;
}

bool operator|(filter_proxy_t p_source, sink_t p_sink)
{
    filter::ringbuf buf;
    bool source_eof = false;
    do {
        while ((!buf.full()) && (!source_eof)) {
            auto slots = buf.continuous_slots();

            auto ret = p_source.read(slots.base, slots.size);

            if (ret >= 0) {
                buf.update_size(slots.size - ret);
            } else if (ret == -eof) {
                source_eof = true;
            } else if (ret == -again) {

            } else
                return false;
        }

        while (!buf.empty()) {
            auto elems = buf.continuous_elems();
            auto ret = p_sink.write(elems.base, elems.size);

            if (ret >= 0) {
                buf.update_size(-(elems.size - ret));
            } else if (ret == -again) {

            } else
                return false;
        }

    } while ((!source_eof) || (!buf.empty()));

    return true;
}

filter_proxy_t operator|(source_t p_source, filter_proxy_t p_filter)
{
    p_filter.set_upstream(p_source);
    return p_filter;
}

} // namespace nx::pipe
