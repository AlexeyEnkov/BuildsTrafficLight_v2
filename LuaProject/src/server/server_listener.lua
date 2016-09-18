local conn = ...
print("new connection ", conn)
_CP[conn] = {}
conn:on("receive",
    function(conn, req)
        if _MAIN_LOCK then
            conn:close()
            print("sorry")
        end
        tmr.wdclr()
        print("recieved", conn)
        local data = _CP[conn]
        if data ~= nil and data.needBody then
            --print("recieved body", req)
            data.body = req
            data.needBody = false
        else
            local _, _, method, path, vars = string.find(req, "([A-Z]+) (.+)?(.+) HTTP")
            if (method == nil) then
                _, _, method, path = string.find(req, "([A-Z]+) (.+) HTTP")
            end
            --data = {}
            --_CP[conn] = data
            data.method = method
            data.path = path
            if (method == "POST") then
                local _, _, body = string.find(req, "\r\n\r\n(.+)")
                if body then
                    data.body = body
                else
                    data.needBody = true
                    --print("need to find body")
                    return -- wait data
                end
            end
        end

        if (cPoolSize() == 1) then
            loadScript("server")(conn, data)
        end
    end)
conn:on("disconnection",
    function(conn)
        tmr.wdclr()
        local data = _CP[conn]
        print("closed", conn, data)
        if data then
            _CP[conn] = nil
        end
        print("conn released")
        if (cPoolSize() > 0) then
            for c, d in pairs(_CP) do
                loadScript("server")(c, d)
                break
            end
        end
    end)