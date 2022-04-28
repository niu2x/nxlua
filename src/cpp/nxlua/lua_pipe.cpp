#include "lua_pipe.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "utils.h"
#include "nx_assert.h"

#include <sstream>
#include <algorithm>
#include <boost/lexical_cast.hpp>

#include <boost/algorithm/string.hpp>

namespace nxlua::lua::pipe {

std::string pipe(const std::string& sz, nx::pipe::filter_proxy_t filter)
{
    std::istringstream is(sz);
    nx::pipe::source_t source(is);

    std::stringstream out;
    nx::pipe::sink_t sink(out);

    source | filter | sink;

    return out.str();
}

namespace {

#define MAX_PARAM_SIZE 3

class filter_desc_t {
public:
    std::string name;
    std::string params[MAX_PARAM_SIZE];
};

std::size_t replace_all(
    std::string& inout, std::string_view what, std::string_view with)
{
    std::size_t count {};
    for (std::string::size_type pos {};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
    return count;
}

std::size_t remove_all(std::string& inout, std::string_view what)
{
    return replace_all(inout, what, "");
}

std::vector<filter_desc_t> filters_desc_parse(const std::string& p_filters_desc)
{
    std::vector<filter_desc_t> result;

    auto filters_desc = p_filters_desc;

    boost::trim(filters_desc);

    // remove_all(filters_desc, " ");

    // boost::replace_all(filters_desc, " ", "");

    std::vector<std::string> strs;
    boost::split(strs, filters_desc, boost::is_any_of("|"));

    for (auto& it : strs) {
        boost::trim(it);

        int op_pos;
        if ((op_pos = it.find('(')) != std::string::npos) {
            filter_desc_t desc { .name = it.substr(0, op_pos) };

            auto params_sz = it.substr(op_pos + 1, it.size() - op_pos - 2);
            boost::trim(params_sz);

            std::vector<std::string> params;
            boost::split(params, params_sz, boost::is_any_of(","));

            for (auto& p : params) {
                boost::trim(p);
            }

            if (params.size() > 0) {
                desc.params[0] = std::move(params[0]);
            }
            if (params.size() > 1) {
                desc.params[1] = std::move(params[1]);
            }
            result.push_back(std::move(desc));
        } else {
            filter_desc_t desc { .name = it };
            result.push_back(std::move(desc));
        }
    }

    return result;
}

} // namespace

std::string pipe(const std::string& sz, const std::string& p_filters_desc)
{
    std::vector<std::unique_ptr<nx::pipe::filter::filter_t>> filters;
    auto filters_desc = filters_desc_parse(p_filters_desc);

#define NO_PARAM_FILTER(NAME)                                                  \
    if (!strcmp(stringify(NAME), desc.name.c_str())) {                         \
        filters.push_back(std::make_unique<nx::pipe::filter::NAME##_t>());     \
    }

    for (auto& desc : filters_desc) {
        // clang-format off
        NO_PARAM_FILTER (hex)
        else NO_PARAM_FILTER(unhex) 
        else NO_PARAM_FILTER(lower) 
        else NO_PARAM_FILTER(upper) 
        else NO_PARAM_FILTER(base64) 
        else NO_PARAM_FILTER(unbase64) 
        else NO_PARAM_FILTER(unzlib) 
        else if(!strcmp(stringify(zlib), desc.name.c_str())) {
            int level = boost::lexical_cast<int>(desc.params[0]);
            filters.push_back(std::make_unique<nx::pipe::filter::zlib_t>(level));
        }
        else if(!strcmp(stringify(digest), desc.name.c_str())) {
            auto algorithm = desc.params[0].c_str();
            filters.push_back(std::make_unique<nx::pipe::filter::digest_t>(algorithm));
        }
        else if(!strcmp(stringify(encrypt), desc.name.c_str())) {
            auto algorithm = desc.params[0].c_str();
            auto key = (const uint8_t*)desc.params[1].c_str();
            auto iv = (const uint8_t*)desc.params[2].c_str();
            filters.push_back(std::make_unique<nx::pipe::filter::encrypt_t>(algorithm, key, iv));
        }
        else if(!strcmp(stringify(decrypt), desc.name.c_str())) {
            auto algorithm = desc.params[0].c_str();
            auto key = (const uint8_t*)desc.params[1].c_str();
            auto iv = (const uint8_t*)desc.params[2].c_str();
            filters.push_back(std::make_unique<nx::pipe::filter::decrypt_t>(algorithm, key, iv));
        }
        else
        {
            NX_ASSERT(false, "unsupported filter %s", desc.name.c_str());
        }
        // clang-format on
    }

#undef NO_PARAM_FILTER

    std::istringstream is(sz);
    nx::pipe::source_t source(is);

    std::stringstream out;
    nx::pipe::sink_t sink(out);

    nx::pipe::filter::filter_t::proxy_t filter_proxy(nullptr);
    bool first = true;

    for (auto& f : filters) {
        if (first) {
            filter_proxy = source | *f;
            first = false;
        } else {
            filter_proxy = filter_proxy | *f;
        }
    }

    filter_proxy | sink;

    return out.str();
}

}; // namespace nxlua::lua::pipe