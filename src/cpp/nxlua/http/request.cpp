#include "request.h"
#include "niu2x/log.h"

#include <sstream>

namespace nxlua::http {

class curl_global_t {
public:
    curl_global_t() { curl_global_init(CURL_GLOBAL_ALL); }
    ~curl_global_t() { curl_global_cleanup(); }
};

static curl_global_t curl_global;

request_t::request_t() { }
request_t::~request_t() { }

static size_t writeFunction(
    void* ptr, size_t size, size_t nmemb, std::stringstream* data)
{
    data->write((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::unique_ptr<response_t> request_t::send()
{
    auto response = std::make_unique<response_t>();

    auto curl = curl_easy_init();
    if (curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 8L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::stringstream response_data;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        auto res = curl_easy_perform(curl);

        response->set_curl_code(res);
        /* Check for errors */
        if (res != CURLE_OK)
            NX_LOG_E(
                "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else {
            int http_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            response->set_http_code(http_code);
            if (http_code >= 200 && http_code < 300) {
                response->set_body(response_data.str());
            }
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
        return response;
    }
    return nullptr;
}

} // namespace nxlua::http