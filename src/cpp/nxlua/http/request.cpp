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

request_t::request_t()
: method_(GET)
{
}

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

        struct curl_slist* header_list = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 8L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        CURLoption curl_methods[] = {
            CURLOPT_HTTPGET,
            CURLOPT_POST,
            CURLOPT_PUT,

        };
        auto curl_method = curl_methods[method_];
        curl_easy_setopt(curl, curl_method, 1L);

        if (method_ == POST) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
        }

        if (header_.size() > 0) {
            for (auto& v : header_) {
                std::stringstream os;
                os << v.first << ":" << v.second;
                header_list = curl_slist_append(header_list, os.str().c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
        }

        std::stringstream response_data;
        std::stringstream response_header;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 4L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 8L);

        printf("preform 1\n");
        auto res = curl_easy_perform(curl);
        printf("preform 2\n");

        response->set_curl_code(res);
        response->set_header(response_header.str());

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

        if (header_list)
            curl_slist_free_all(header_list);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return response;
}

void request_t::set_header(const std::string& key, std::string value)
{
    header_[key] = std::move(value);
}

} // namespace nxlua::http