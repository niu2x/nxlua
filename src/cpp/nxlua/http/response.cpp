#include "response.h"

namespace nxlua::http {

response_t::response_t()
: http_code_(-1)
, curl_code_(-1)
{
}
response_t::~response_t() { }

} // namespace nxlua::http