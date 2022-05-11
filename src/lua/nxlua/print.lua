local oldprint = _G.print
_G.print = function ( ... )
	local first = true
	for k, v in ipairs({...}) do
		if first then
			first = false
		else
			io.stdout:write(' ')
		end
		if type(v) == 'table' then
			io.stdout:write(table.tostring(v))
		elseif type(v) ~= 'string' then
			io.stdout:write(tostring(v))
		else
			io.stdout:write(v)
		end
	end
	io.stdout:write('\n')
end
