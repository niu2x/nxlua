#include "tableExt.h"
static const char* source = R"RAW(
function table.each(t, func)
	for k, v in pairs(t) do
		if func(v, k) == true then
			return true
		end
	end
	return false
end

function table.indexEach(t, func)
	for index = 1, #t do
		if func(t[index], index) == true then
			return true
		end
	end
	return false
end

function table.reverseIndexEach(t, func)
	for index = #t, 1, -1 do
		if func(t[index], index) == true then
			return true
		end
	end
	return false
end

function table.filter(t, func)
	local ret = {}
	for k, v in pairs(t) do
		if func(v) == true then
			table.insert(ret, v)
		end
	end
	return ret
end

function table.map(func, ...)
	local paras = {...}
	local tables = paras
	local ret = {}
	for k, v in pairs(tables[1]) do
		local values = {}
		for _, t in ipairs(tables) do
			values[#values + 1] = t[k]
		end
		ret[k] = func(table.unpack(values))
	end
	return ret
end

function table.sum(t)
	return table.reduce(t, function(a, b)
		return a + b
	end)
end

function table.reduce(t, func)
	local ret = t[1]
	local index = 2
	while index <= #t do
		ret = func(ret, t[index])
		index = index + 1
	end
	return ret
end

function table.clone(t, meta)
	local u = {}

	if nometa then
    	setmetatable(u, getmetatable(t))
	end

	for i, v in pairs(t) do
		if type(v) == "table" then
    		u[i] = table.clone(v)
		else
			u[i] = v
		end
	end

	return u
end

function table.simpleClone(t)
	return table.map(t, function(v) return v end)
end

function table.indexOf(t, v)
    for i, v_ in ipairs(t) do
        if v_ == v then return i end
    end
    return nil
end

function table.keyOf(t, v)
    for k, v_ in pairs(t) do
        if v_ == v then return k end
    end
    return nil
end

function table.removeValue(t, value)
	local index = table.indexOf(t, value)
	if index then 
		table.remove(t, index) 
  		return
 	end

	local key = table.keyOf(t, value)
	if key then 
		t[key] = nil 
	end
end

function table.unique(t)
	local seen = {}
	for i, v in ipairs(t) do
		if not table.includes(seen, v) then table.insert(seen, v) end
	end
	return seen
end

function table.union(t0, t1)
    local t = {}
    for i, v in ipairs(t0) do table.insert(t, v) end
    for i, v in ipairs(t1) do table.insert(t, v) end
    return t
end

function table.merge(t0, t1)
    local t = {}
    for k, v in pairs(t0) do t[k] = v end
    for k, v in pairs(t1) do t[k] = v end
    return t
end

function table.removeAll(t)
    for k, v in pairs(t) do 
    	t[k] = nil
    end
end

function table.keys(t)
	local keys = {}
	for k, v in pairs(t) do 
		table.insert(keys, k) 
	end
	return keys
end

function table.values(t)
	local values = {}
	for k, v in pairs(t) do 
		table.insert(values, v) 
	end
	return values
end

function table.last(t)
	return t[#t]
end

function table.append(t, moreValues)
	for i, v in ipairs(moreValues) do
		table.insert(t, v)
	end
	return t
end

function table.find(t, func)
	for k, v in pairs(t) do
		if func(v) then 
			return v, k 
		end
	end
	return nil
end

function table.groupBy(t, func)
	local grouped = {}
	for k, v in pairs(t) do
		local groupKey = func(v)
		if not grouped[groupKey] then 
			grouped[groupKey] = {} 
		end
		table.insert(grouped[groupKey], v)
	end
	return grouped
end

function table.tostring(tbl, indent, limit, depth, jstack)
	limit   = limit  or 1000
	depth   = depth  or 7
	jstack  = jstack or {name="top"}
	local i = 0

	local output = {}
	if type(tbl) == "table" then
    -- very important to avoid disgracing ourselves with circular referencs...
		for i,t in pairs(jstack) do
    		if tbl == t then
      			return "<" .. i .. ">,\n"
    		end
    	end
    	jstack[jstack.name] = tbl

    	table.insert(output, "{\n")

    	local name = jstack.name
	    for key, value in pairs(tbl) do
	      	local innerIndent = (indent or " ") .. (indent or " ")
	      	table.insert(output, innerIndent .. tostring(key) .. " = ")
	      	jstack.name = name .. "." .. tostring(key)
	      	table.insert(output,
	        	value == tbl and "<parent>," or table.tostring(value, innerIndent, limit, depth, jstack)
	      	)

	      	i = i + 1
	     	if i > limit then
	        	table.insert(output, (innerIndent or "") .. "...\n")
	        	break
	      	end
	    end

    	table.insert(output, indent and (indent or "") .. "},\n" or "}")
  	else
    	if type(tbl) == "string" then tbl = string.format("%q", tbl) end -- quote strings
    	table.insert(output, tostring(tbl) .. ",\n")
  	end

  	return table.concat(output)
end

function table.insertIfNotExist(t, v)
    if t then
        if not table.indexOf(t, v) then table.insert(t, v) end
    else
        t = {v}
    end
    return t
end

function table.removeIfExist(t, v)
    if t then
        local i = table.indexOf(t, v)
        if i then return table.remove(t, i) end
        for k, v_ in pairs(t) do
            if v_ == v then t[k] = nil; return v_; end
        end
    end
    return nil
end

function table.size(t)
    local s = 0
    for k,v in pairs(t) do
        if v ~= nil then 
        	s = s+1
        end
    end
    return s;
end

function table.exist(t,v)
    for k,v_ in pairs(t) do
        if v_ == v then
            return true
        end
    end
    return false
end
)RAW";

#include <iostream>
void pure_lua_tableExt_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}
