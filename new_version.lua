#!/usr/bin/env nxlua

local t = sys.argv[2]

local upgrade_types = {
	'major',
	'minor',
	'patch',
}

local function usage( ... )
	print(string.format("Usage: %s major/minor/patch", sys.argv[1]))
	os.exit(1)
end

if not table.exist(upgrade_types, t) then
	print(sys.argv[1], "invalid arguments")
	usage()
end

local function readfile( pathname )
	local f = io.open(pathname)
	local v = f:read('*all')
	f:close()
	return v
end

local function writefile( pathname, content )
	local f = io.open(pathname, 'wb')
	f:write(content)
	f:close()
end

local mydir = path_utils:dirname(sys.launcher)
local version_file = path_utils:join(mydir, 'VERSION')

local current_version = readfile(version_file):trim()
local fields = current_version:split('.')
assert(#fields == 3, "version format invalid")

local major = tonumber(fields[1])
local minor = tonumber(fields[2])
local patch = tonumber(fields[3])

if t == 'major' then
	major = major + 1
	minor = 0
	patch = 0
end

if t == 'minor' then
	minor = minor + 1
	patch = 0
end

if t == 'patch' then
	patch = patch + 1
end

local version = string.format('%d.%d.%d', major, minor, patch)
writefile(version_file, version .. '\n')

os.execute(F[[git commit VERSION -m "update version to {version}"]])
os.execute(F[[git tag -a "v{version}" -m "create tag v{version}" -s]])
