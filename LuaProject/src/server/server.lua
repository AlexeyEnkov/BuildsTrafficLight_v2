local bodyHandler
return function(c, request)
    local q = require("queue")
    if bodyHandler then
        q(bodyHandler, c, request)
        bodyHandler = nil
        return
    end
    local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP")
    if (method == nil) then
        _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP")
    end
    local sender = require("sender")
    if (path == "/favicon.ico") then
        q(require("send_file"), c, "favicon.png")
        return
    end
    if (method == "POST" and path == "/settings") then
        bodyHandler = require("settings_handler")
        local _, _, body = string.find(request, "\r\n\r\n(.+)")

        if body then
            q(bodyHandler, c, request)
            bodyHandler = nil
        end

        return
    end
    q(require("start_page"), c)

    require("clear")()
end
