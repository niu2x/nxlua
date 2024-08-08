#ifndef NX_RINGBUF_H
#define NX_RINGBUF_H

#include <string.h>

#include <cstddef>
#include <algorithm>

namespace nx {

template <class Elem, size_t capacity = 1024>
class ringbuf_t {
public:
    template <class T>
    struct arrayref {
        T* base;
        size_t size;
    };

    static constexpr size_t user_capacity = capacity - 1;

    ringbuf_t()
    : head_(0)
    , tail_(0)
    {
    }
    ~ringbuf_t() { }

    ringbuf_t(const ringbuf_t&) = default;
    ringbuf_t& operator=(const ringbuf_t&) = default;

    bool full() const noexcept { return size() == user_capacity; }

    bool empty() const noexcept { return size() == 0; }

    bool put(const Elem& e) noexcept { return put(&e, 1, nullptr); }

    bool put(const Elem* input, size_t isize, size_t* osize) noexcept
    {
        auto rooms = user_capacity - size();
        auto writen = std::min(isize, rooms);
        if (osize)
            *osize = writen;

        if (!writen)
            return false;

        if (tail_ >= head_) {
            auto n = std::min(capacity - tail_, writen);
            memcpy(data_ + tail_, input, n * sizeof(Elem));
            input += n;
            writen -= n;
            tail_ = add(tail_, n);
        }

        if (writen) {
            memcpy(data_ + tail_, input, writen * sizeof(Elem));
            tail_ = add(tail_, writen);
        }

        return true;
    }

    bool get(Elem* output, size_t max_osize, size_t* osize) noexcept
    {
        auto my_size = size();
        if (!my_size)
            return false;

        auto readn = std::min(max_osize, my_size);
        if (osize)
            *osize = readn;

        if (tail_ >= head_) {
            memcpy(output, data_ + head_, readn * sizeof(Elem));
        } else {
            memcpy(output, data_ + head_,
                std::min(capacity - head_, readn) * sizeof(Elem));
            if (readn > capacity - head_) {
                memcpy(output + capacity - head_, data_,
                    readn - (capacity - head_) * sizeof(Elem));
            }
        }

        head_ = add(head_, readn);
        return true;
    }

    bool get(Elem& out) noexcept { return get(&out, 1, nullptr); }

    size_t size() const noexcept { return minus(tail_, head_); }

    void update_size(int delta) noexcept
    {
        if (delta > 0) {
            tail_ = add(tail_, std::min((size_t)delta, user_capacity - size()));
        } else {
            head_ = add(head_, std::min((size_t)(-delta), size()));
        }
    }

    arrayref<Elem> continuous_elems() noexcept
    {
        if (tail_ >= head_) {
            return arrayref<Elem> { data_ + head_, tail_ - head_ };
        } else {
            return arrayref<Elem> { data_ + head_, capacity - head_ };
        }
    }

    arrayref<Elem> continuous_slots() noexcept
    {
        if (tail_ >= head_) {
            if (head_) {
                return arrayref<Elem> { data_ + tail_, capacity - tail_ };
            } else {
                return arrayref<Elem> { data_ + tail_, user_capacity - tail_ };
            }
        } else {
            return arrayref<Elem> { data_ + tail_, head_ - tail_ - 1 };
        }
    }

    void normalize()
    {
        if (head_) {
            Elem temp[capacity];
            memcpy(temp, data_ + head_, (capacity - head_) * sizeof(Elem));
            memcpy(temp + capacity - head_, data_, (head_) * sizeof(Elem));
            memcpy(data_, temp, capacity * sizeof(Elem));
            size_t s = size();
            head_ = 0;
            tail_ = s;
        }
    }

private:
    Elem data_[capacity];
    size_t head_;
    size_t tail_;

    static size_t minus(size_t a, size_t b) noexcept
    {
        if (a < b)
            return a + capacity - b;
        return a - b;
    }

    static size_t add(size_t a, size_t b) noexcept
    {
        size_t sum = a + b;
        if (sum >= capacity)
            sum -= capacity;
        return sum;
    }
};

} // namespace nx

#endif