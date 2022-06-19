local dhttp = {}

function dhttp:get(url, opts)
	opts = opts or {}
	opts.retry = opts.retry or 2

	local d = opts.d or deferred.new()
	opts.d = d

	local req = http.request_t()
	req:set_url(url)
	req:set_method(http.GET)
	http.send(req, function(resp)
		local http_code = resp:http_code()
		if http_code >= 200 and http_code < 300 then
			d:resolve(resp)
		else
			if opts.retry > 0 then
				opts.retry = opts.retry - 1
				dhttp:get(url, opts)
			else
				d:reject(resp)
			end
		end
	end)
	return d;
end

_G.dhttp = dhttp