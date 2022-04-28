#include "../pipe.h"

#include <string.h>

#define OPENSSL_NO_DEPRECATED 1
#include <openssl/evp.h>
#include <openssl/err.h>

#include "nxlua/nx_assert.h"

#define OPENSSL_CHECK(condition, message)                                      \
    if (!(condition)) {                                                        \
        auto e = ERR_peek_last_error();                                        \
        NX_LOG_F("%s reason: %d %s", message, e, ERR_reason_error_string(e));  \
        NX_THROW(message);                                                     \
    }

namespace nx::pipe::filter {

cipher_t::cipher_t(const char* p_algorithm_name, int mode, const uint8_t key[],
    const uint8_t iv[])
{
    auto* algorithm = EVP_get_cipherbyname(p_algorithm_name);
    OPENSSL_CHECK(algorithm != nullptr, "invalid cipher algorithm");

    auto* ctx = EVP_CIPHER_CTX_new();
    OPENSSL_CHECK(ctx != nullptr, "invalid cipher ctx");
    cipher_ctx_ = ctx;

    EVP_CipherInit_ex2(ctx, algorithm, key, iv, mode, nullptr);
}

cipher_t::~cipher_t()
{
    auto* ctx = reinterpret_cast<EVP_CIPHER_CTX*>(cipher_ctx_);
    EVP_CIPHER_CTX_free(ctx);
}

bool cipher_t::transform(ringbuf& rbuf, ringbuf& wbuf, bool upstream_eof)
{
    auto* ctx = reinterpret_cast<EVP_CIPHER_CTX*>(cipher_ctx_);

    auto input = rbuf.continuous_elems();
    auto output = wbuf.continuous_slots();

    if (input.size > 0) {
        auto isize = std::min(
            (int)input.size, (int)(output.size - EVP_MAX_BLOCK_LENGTH + 1));

        if (isize > 0) {
            int iwriten;
            int status = EVP_CipherUpdate(
                ctx, output.base, &iwriten, input.base, isize);

            OPENSSL_CHECK(status != 0,
                (std::string("EVP_CipherUpdate fail ") + std::to_string(status))
                    .c_str());

            rbuf.update_size(-isize);
            wbuf.update_size(iwriten);
        }
    }
    if (rbuf.empty() && upstream_eof) {
        auto output = wbuf.continuous_slots();
        if (output.size >= EVP_MAX_BLOCK_LENGTH) {
            int iwriten;
            int status = EVP_CipherFinal_ex(ctx, output.base, &iwriten);
            OPENSSL_CHECK(status != 0,
                (std::string("EVP_CipherFinal_ex fail ")
                    + std::to_string(status))
                    .c_str());

            wbuf.update_size(iwriten);
            return true;
        } else {
            NX_LOG_E("no enough space for EVP_CipherFinal_ex");
        }
    }
    return false;
}

} // namespace nx::pipe::filter
