-- print([==[todo add script root dir to package.path]==])
local non_interactive = sys.argv[1] ~= nil
if non_interactive then
	local launcher = path_utils:join(os.getcwd(), sys.argv[1])
	package.path = string.format("%s/?.lua;", path_utils:dirname(launcher)) .. package.path 
end

