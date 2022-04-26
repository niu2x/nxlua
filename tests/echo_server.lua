local tcp = luv.new_tcp()
tcp:bind('127.0.0.1', 8888)
tcp:listen(128, function(err)
    if err then return end

    local client_tcp = luv.new_tcp()
    tcp:accept(client_tcp)

	print("create client_tcp", client_tcp)
    client_tcp:read_start(function(err, chunk)
    	if err then 
    		client_tcp:close()
    		print("error close client_tcp", client_tcp)
    		return 
    	end

    	if chunk then
    		client_tcp:write(chunk)
    	else
    		print("close client_tcp", client_tcp)
    		client_tcp:close()
    	end
    end)

end)

luv.run()