_CONN_POOL = {}
local function poolSize()
    local ind = 0;
    for k, _ in pairs(_CONN_POOL) do
        ind = ind + 1;
    end
    return ind
end

return function(conn)
    require("clear")()
    collectgarbage("restart")
    conn:on("receive",
        function(conn, req)
            for k, v in pairs(conn) do
                print("conn", k, v)
            end
            print("recieved", conn)
            local data = _CONN_POOL[conn]
            if data ~= nil and data.needBody then
                print("recieved body", req, "psize", poolSize())
                data.body = req
                data.needBody = false
            else
                local _, _, method, path, vars = string.find(req, "([A-Z]+) (.+)?(.+) HTTP")
                if (method == nil) then
                    _, _, method, path = string.find(req, "([A-Z]+) (.+) HTTP")
                end
                data = {}
                _CONN_POOL[conn] = data
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
                pcall(require("server"), conn, data)
            end
        end)
    conn:on("disconnection",
        function(conn)
            print("closed", conn, "pzise", poolSize())
            local data = _CONN_POOL[conn]
            print(data.path, data.method, data.body)
            --_CONN_POOL[conn] = nil
            if (poolSize() > 0) then
                for c, d in pairs(_CONN_POOL) do
                    pcall(require("server"), c, d)
                    break
                end
            end
        end)
end