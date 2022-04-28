#include "stringExt.h"
static const char* source = R"RAW(
function string:ltrim()
	return self:match('^[ \t\n\r]*(.-)$')
end

function string:rtrim()
	return self:match('^(.-)[ \t\n\r]*$')
end

function string:trim()
	return self:ltrim():rtrim()
end

function string:split(sep)
	local sep, fields = sep or ":", {}
	local pattern = string.format("([^%s]+)", sep)
	self:gsub(pattern, function(c) fields[#fields+1] = c end)
	return fields
end

function string.startswith(String, Start)
   return string.sub(String,1,string.len(Start))==Start
end

function string.endswith(String, End)
   return End =='' or string.sub(String,-string.len(End))==End
end

local _htmlspecialchars_set = {}
_htmlspecialchars_set["&"] = "&amp;"
_htmlspecialchars_set['"'] = "&quot;"
_htmlspecialchars_set["'"] = "&#039;"
_htmlspecialchars_set["<"] = "&lt;"
_htmlspecialchars_set[">"] = "&gt;"

function string.htmlspecialchars(input)
    for k, v in pairs(_htmlspecialchars_set) do
        input = string.gsub(input, k, v)
    end
    return input
end

function string.restorehtmlspecialchars(input)
    for k, v in pairs(_htmlspecialchars_set) do
        input = string.gsub(input, v, k)
    end
    return input
end

function string.nl2br(input)
    return string.gsub(input, "\n", "<br />")
end

function string.text2html(input)
    input = string.gsub(input, "\t", "    ")
    input = string.htmlspecialchars(input)
    input = string.gsub(input, " ", "&nbsp;")
    input = string.nl2br(input)
    return input
end


local function urlencodechar(char)
    return "%" .. string.format("%02X", string.byte(char))
end
function string.urlencode(input)
    -- convert line endings
    input = string.gsub(tostring(input), "\n", "\r\n")
    -- escape all characters but alphanumeric, '.' and '-'
    input = string.gsub(input, "([^%w%.%- ])", urlencodechar)
    -- convert spaces to "+" symbols
    return string.gsub(input, " ", "+")
end

function string.urldecode(input)
    input = string.gsub (input, "+", " ")
    input = string.gsub (input, "%%(%x%x)", function(h) return string.char(checknumber(h,16)) end)
    input = string.gsub (input, "\r\n", "\n")
    return input
end

function string.utf8len(input)
    local len  = string.len(input)
    local left = len
    local cnt  = 0
    local arr  = {0, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc}
    while left ~= 0 do
        local tmp = string.byte(input, -left)
        local i   = #arr
        while arr[i] do
            if tmp >= arr[i] then
                left = left - i
                break
            end
            i = i - 1
        end
        cnt = cnt + 1
    end
    return cnt
end
)RAW";

#include <iostream>
void pure_lua_stringExt_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}
