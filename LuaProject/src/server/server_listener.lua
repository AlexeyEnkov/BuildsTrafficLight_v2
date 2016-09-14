local conn = ...

local function poolSize()
    local ind = 0;
    for k, _ in pairs(_CP) do
        ind = ind + 1;
    end
    return ind
end

conn:on("receive",
    function(conn, req)
        print("recieved", conn)
        local data = _CP[conn]
        if data ~= nil and data.needBody then
            print("recieved body", req)
            data.body = req
            data.needBody = false
        else
            local _, _, method, path, vars = string.find(req, "([A-Z]+) (.+)?(.+) HTTP")
            if (method == nil) then
                _, _, method, path = string.find(req, "([A-Z]+) (.+) HTTP")
            end
            data = {}
            _CP[conn] = data
            data.method = method
            data.path = path
            if (method == "POST") then
                local _, _, body = string.find(req, "\r\n\r\n(.+)")
                if body then
                    data.body = body
                else
                    data.needBody = true
                    print("need to find body")
                    return -- wait data
                end
            end
        end

        if (poolSize() == 1) then
            loadScript("server")(conn, data)
        end
    end)
conn:on("disconnection",
    function(conn)
        print("closed", conn)
        local data = _CP[conn]
        if data then
            _CP[conn] = nil
        end
        if (poolSize() > 0) then
            for c, d in pairs(_CP) do
                loadScript("server")(c, d)
                break
            end
        end
    end)