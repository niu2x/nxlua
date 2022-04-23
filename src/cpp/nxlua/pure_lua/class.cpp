#include "class.h"
static const char* source = R"RAW(
local baseClass = {class = true}
baseClass.__index = baseClass

function baseClass:ctor()
end

function baseClass:new(...)
	local classObj = self
	local instance = {}
	setmetatable(instance, classObj)
	instance:ctor(...)
	return instance
end

local function class(super)
	super = super or baseClass
	local classObj = {class = true}
	classObj.__index = classObj
	setmetatable(classObj, super)
	return classObj
end

_G.class = class
)RAW";

void pure_lua_class_open(lua_State* L) { luaL_dostring(L, source); }
