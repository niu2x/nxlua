#ifndef NX_PIPE_H
#define NX_PIPE_H

#include <iostream>
#include <functional>
#include <variant>
#include <string>

#include <boost/noncopyable.hpp>

#include "ringbuf.h"

namespace nx::pipe {

enum status {
    ok = 0,
    again,
    eof,
    fail,
};

class source_t {
public:
    source_t(std::istream& stream);
    ~source_t();

    source_t(const source_t&) = default;
    source_t(source_t&&) = default;
    source_t& operator=(const source_t&) = default;
    source_t& operator=(source_t&&) = default;

    int read(void* data, size_t bytes);

private:
    std::variant<std::istream*> delegate_;
};

class sink_t {
public:
    sink_t(std::ostream& stream);
    ~sink_t();

    sink_t(const sink_t&) = default;
    sink_t& operator=(const sink_t&) = default;

    int write(const void* data, size_t bytes);

private:
    std::variant<std::ostream*> delegate_;
};

namespace filter {

using ringbuf = nx::ringbuf_t<uint8_t, 4096>;

class filter_t : private boost::noncopyable {
public:
    class proxy_t {
    public:
        proxy_t(filter_t* p_filter)
        : delegate_(p_filter)
        {
        }
        ~proxy_t() { }
        proxy_t(const proxy_t&) = default;
        proxy_t& operator=(const proxy_t&) = default;
        int read(void* data, size_t bytes)
        {
            return delegate_->read(data, bytes);
        }

        void set_upstream(source_t p_upstream)
        {
            delegate_->set_upstream(p_upstream);
        }
        void set_upstream(proxy_t p_upstream)
        {
            delegate_->set_upstream(p_upstream);
        }

    private:
        filter_t* delegate_;
    };

    filter_t();
    virtual ~filter_t();

    int read(void* data, size_t bytes);

    void set_upstream(source_t p_upstream);
    void set_upstream(proxy_t p_upstream);

    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof) = 0;

    proxy_t proxy() noexcept { return proxy_t(this); }

    operator proxy_t() noexcept { return proxy(); }

private:
    void read_from_upstream();
    int write_to_downstream(void* data, size_t bytes);

    std::variant<source_t, proxy_t, std::nullptr_t> upstream_;
    ringbuf rbuf_;
    ringbuf wbuf_;
    bool upstream_eof_;
    bool transform_eof_;
};

class simple_filter_t : public filter_t {
public:
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);
    virtual uint8_t transform(uint8_t chr) = 0;
};

class lower_t : public simple_filter_t {
public:
    virtual uint8_t transform(uint8_t chr) { return tolower(chr); }
};

class upper_t : public simple_filter_t {
public:
    virtual uint8_t transform(uint8_t chr) { return toupper(chr); }
};

class hex_t : public filter_t {
public:
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);
};

class unhex_t : public filter_t {
public:
    unhex_t();
    virtual ~unhex_t() { }
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    uint8_t buf_[2];
    uint8_t size_;
};

class base64_t : public filter_t {
public:
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);
};

class unbase64_t : public filter_t {
public:
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);
};

class cut_t : public filter_t {
public:
    cut_t(uint8_t chr);
    virtual ~cut_t() { }
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    uint8_t chr_;
};

class zlib_t : public filter_t {
    enum { default_level = 6 };

public:
    zlib_t(int level = default_level);
    virtual ~zlib_t();

    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    void* zlib_ctx_;
};

class unzlib_t : public filter_t {
public:
    unzlib_t();
    virtual ~unzlib_t();
    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    void* zlib_ctx_;
};

class digest_t : public filter_t {
public:
    /**
     * @brief      { function_description }
     *
     * @param[in]  algorithm  The algorithm:
                                "blake2b512",
                                "blake2s256",
                                "md5",
                                "md5-sha1",
                                "sha1",
                                "sha224",
                                "sha256",
                                "sha3-224",
                                "sha3-256",
                                "sha3-384",
                                "sha3-512",
                                "sha384",
                                "sha512",
                                "sha512-224",
                                "sha512-256",
                                "shake128",
                                "shake256",
                                "sm3",
                                "ssl3-md5",
                                "ssl3-sha1",
     */
    digest_t(const char* algorithm);
    virtual ~digest_t();

    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    void* digest_ctx_;
};

class cipher_t : public filter_t {
public:
    /**
     * @brief      { function_description }
     *
     * @param[in]  algorithm  The algorithm:
                                    "aes-128-cbc",
                                    "aes-128-cfb",
                                    "aes-128-cfb1",
                                    "aes-128-cfb8",
                                    "aes-128-ctr",
                                    "aes-128-ecb",
                                    "aes-128-ofb",
                                    "aes-192-cbc",
                                    "aes-192-cfb",
                                    "aes-192-cfb1",
                                    "aes-192-cfb8",
                                    "aes-192-ctr",
                                    "aes-192-ecb",
                                    "aes-192-ofb",
                                    "aes-256-cbc",
                                    "aes-256-cfb",
                                    "aes-256-cfb1",
                                    "aes-256-cfb8",
                                    "aes-256-ctr",
                                    "aes-256-ecb",
                                    "aes-256-ofb",
                                    "aes128",
                                    "aes192",
                                    "aes256",
                                    "aria-128-cbc",
                                    "aria-128-cfb",
                                    "aria-128-cfb1",
                                    "aria-128-cfb8",
                                    "aria-128-ctr",
                                    "aria-128-ecb",
                                    "aria-128-ofb",
                                    "aria-192-cbc",
                                    "aria-192-cfb",
                                    "aria-192-cfb1",
                                    "aria-192-cfb8",
                                    "aria-192-ctr",
                                    "aria-192-ecb",
                                    "aria-192-ofb",
                                    "aria-256-cbc",
                                    "aria-256-cfb",
                                    "aria-256-cfb1",
                                    "aria-256-cfb8",
                                    "aria-256-ctr",
                                    "aria-256-ecb",
                                    "aria-256-ofb",
                                    "aria128",
                                    "aria192",
                                    "aria256",
                                    "camellia-128-cbc",
                                    "camellia-128-cfb",
                                    "camellia-128-cfb1",
                                    "camellia-128-cfb8",
                                    "camellia-128-ctr",
                                    "camellia-128-ecb",
                                    "camellia-128-ofb",
                                    "camellia-192-cbc",
                                    "camellia-192-cfb",
                                    "camellia-192-cfb1",
                                    "camellia-192-cfb8",
                                    "camellia-192-ctr",
                                    "camellia-192-ecb",
                                    "camellia-192-ofb",
                                    "camellia-256-cbc",
                                    "camellia-256-cfb",
                                    "camellia-256-cfb1",
                                    "camellia-256-cfb8",
                                    "camellia-256-ctr",
                                    "camellia-256-ecb",
                                    "camellia-256-ofb",
                                    "camellia128",
                                    "camellia192",
                                    "camellia256",
                                    "chacha20",
                                    "des3",
                                    "sm4",
                                    "sm4-cbc",
                                    "sm4-cfb",
                                    "sm4-ctr",
                                    "sm4-ecb",
                                    "sm4-ofb",

     */

    enum { decrypt = 0, encrypt = 1 };

    cipher_t(const char* algorithm, int mode, const uint8_t key[],
        const uint8_t iv[]);
    virtual ~cipher_t();

    virtual bool transform(ringbuf&, ringbuf&, bool upstream_eof);

private:
    void* cipher_ctx_;
};

class encrypt_t : public cipher_t {
public:
    encrypt_t(const char* algorithm, const uint8_t key[], const uint8_t iv[])
    : cipher_t(algorithm, encrypt, key, iv)
    {
    }
    virtual ~encrypt_t() { }
};

class decrypt_t : public cipher_t {
public:
    decrypt_t(const char* algorithm, const uint8_t key[], const uint8_t iv[])
    : cipher_t(algorithm, decrypt, key, iv)
    {
    }
    virtual ~decrypt_t() { }
};

extern filter_t::proxy_t operator|(
    filter_t::proxy_t p_source, filter_t::proxy_t p_filter);

}; // namespace filter

using filter_proxy_t = filter::filter_t::proxy_t;

extern bool operator|(source_t p_source, sink_t p_sink);

extern bool operator|(filter::filter_t::proxy_t p_filter, sink_t p_sink);

extern filter_proxy_t operator|(source_t p_source, filter_proxy_t p_filter);

} // namespace nx::pipe

#endif