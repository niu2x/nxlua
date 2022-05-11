#include "path_utils.h"
static const char* source = R"RAW(
local path_utils = {}

function path_utils:join( path1, path2 )
	if string.sub(path2, 1, 1) == '/' then
		path2 = string.sub(path2, 2)
	end
	if string.sub(path1, #path1, #path1) == '/' then
		path1 = string.sub(path1, 1, -2)
	end
	return self:normalize(path1 .. '/' .. path2)
end

function path_utils:dirname( path )
	path = self:normalize(path)
	local basename = self:basename(path)
	return self:normalize(string.sub(path, 1,-(#basename)-1))
end

function path_utils:basename( path )
	path = self:normalize(path)
	local fields = path:split('/') or {}
	if #fields >= 1 then
		return fields[#fields]
	end
	return path;
end

function path_utils:normalize( path )
	path = path:gsub('\\', '/')

	while string.endswith(path, '/') do
		path = string.sub(path, 1, #path-1)
	end

	if path == '' then
		path = '/'
	end
	return path
end



function path_utils:splitext( path )
	path = self:normalize(path)
	local basename = self:basename(path)
	local fields = basename:split('.') or {}

	local ext = ''
	if #fields >= 2 then
		ext = fields[#fields]
	end
	path = string.sub(path, 1, -(#ext)-2)
	return path, ext
end




_G.path_utils = path_utils
)RAW";

#include <iostream>
void pure_lua_path_utils_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        {
            std::cerr << lua_tostring(L, -1) << std::endl;
        }
    }
}
