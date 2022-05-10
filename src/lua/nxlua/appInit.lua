-- print([==[todo add script root dir to package.path]==])
local non_interactive = sys.argv[1] ~= nil
if non_interactive then
	local launcher = sys.argv[1]
	if os.is_relative(launcher) then
		launcher = path_utils:join(os.getcwd(), sys.argv[1])
	end
	package.path = string.format("%s/?.lua;", path_utils:dirname(launcher)) .. package.path 
end

