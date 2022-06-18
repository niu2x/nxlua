local dhttp = {}

function dhttp:get(url)
	local d = deferred.new()
	local req = http.request_t()
	req:set_url(url)
	req:set_method(http.GET)
	http.send(req, function(resp)
		local http_code = resp:http_code()
		if http_code >= 200 and http_code < 300 then
			d:resolve(resp)
		else
			d:reject(resp)
		end
	end)
	return d;
end

_G.dhttp = dhttp