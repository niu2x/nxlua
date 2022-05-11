#include "Image.h"
static const char* source = R"RAW(
_G.Image = class()

function Image:ctor()
	self.backend_ = image_t()
end

function Image:load(pathname)
	return self.backend_:load(pathname)
end

function Image:save(pathname)
	return self.backend_:save(pathname)
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

function Image:fill(r,g,b,a)
	self.backend_:fill(r,g,b,a)
end

local function rotate_point(x, y, angle)
	return x * math.cos(angle) - y * math.sin(angle),  x * math.sin(angle) + y * math.cos(angle)
end


function Image:rotate(angle)
	local half_w = self:width()/2
	local half_h = self:height()/2
	local x1, y1 = -half_w, -half_h
	local x2, y2 = -half_w, half_h
	local x3, y3 = half_w, half_h
	local x4, y4 = half_w, -half_h

	x1, y1 = rotate_point(x1, y1, angle)
	x2, y2 = rotate_point(x2, y2, angle)
	x3, y3 = rotate_point(x3, y3, angle)
	x4, y4 = rotate_point(x4, y4, angle)

	local max_x = math.max(math.max(x1, x2), math.max(x3, x4))
	local max_y = math.max(math.max(y1, y2), math.max(y3, y4))

	local min_x = math.min(math.min(x1, x2), math.min(x3, x4))
	local min_y = math.min(math.min(y1, y2), math.min(y3, y4))


	local new_w = max_x - min_x
	local new_h = max_y - min_y

	local result = Image:new_local()
	result:resize(new_w, new_h)
	result:fill(0, 0, 0, 0)


	local transform = image_transform_t:translate(-new_w/2, -new_h/2)
	transform = transform:mul(image_transform_t:rotate(angle))
	transform = transform:mul(image_transform_t:translate(half_w, half_h))
	image_t:resample(
		self.backend_, 0, 0, self:width(), self:height(),
		result.backend_, 0, 0, new_w, new_h,
		transform
	)

	return result

end

function Image:crop(x, y, w, h)
	local result = Image:new_local()
	result:resize(w, h)

	local transform = image_transform_t:translate(0 ,0)
	image_t:resample(
		self.backend_, x, y, w, h,
		result.backend_, 0, 0, w, h,
		transform
	)

	return result
end

function Image:scaleTo(w, h)
	local result = Image:new_local()
	result:resize(w, h)

	local transform = image_transform_t:scale(self:width()/w ,self:height()/h)
	image_t:resample(
		self.backend_, 0, 0, self:width(), self:height(),
		result.backend_, 0, 0, w, h,
		transform
	)

	return result
end

function Image:scale(sx, sy)
	sy = sy or sx
	return self:scaleTo(
		self:width() * sx,
		self:height() * sy
	)
end

-- x, y is lefttop position
function Image:draw(src, x, y)
	-- local src_width = src:width()
	-- local src_height = src:height()

	-- local transform = image_transform_t()
	-- image_t:resample(
	-- 	src.backend_, 0, 0, src_width, src_height,
	-- 	self.backend_, x, y, src_width, src_height,
	-- 	transform
	-- )
	self.backend_:draw(src.backend_, x, y)

end
)RAW";

#include <iostream>
void pure_lua_Image_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        {
            std::cerr << lua_tostring(L, -1) << std::endl;
        }
    }
}
