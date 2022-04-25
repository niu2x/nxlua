#include "Image.h"
static const char* source = R"RAW(
_G.Image = class()

function Image:ctor()
	self.backend_ = image_t()
end

function Image:load(pathname)
	self.backend_:load(pathname)
end

function Image:save(pathname)
	self.backend_:save(pathname)
end

function Image:width( ... )
	return self.backend_:width()
end

function Image:height( ... )
	return self.backend_:height()
end

function Image:resize(w, h)
	self.backend_:resize(w, h)
end
)RAW";

void pure_lua_Image_open(lua_State* L) { luaL_dostring(L, source); }
