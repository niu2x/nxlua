#ifndef NXLUA_HTTP_SEND_H
#define NXLUA_HTTP_SEND_H

#include <memory>

#include "request.h"
#include "response.h"

namespace nxlua::http {

using send_callback_t = void (*) (std::unique_ptr<response_t>);
void send(std::unique_ptr<request_t> request, send_callback_t callback);

}

#endif