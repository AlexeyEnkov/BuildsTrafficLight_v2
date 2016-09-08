local bodyHandler
return function(c, request)
    --print(request)
    local q = require("queue")
    if bodyHandler then
        q(bodyHandler, c, request)
        bodyHandler = nil
        request = nil
        return
    end
    local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP")
    if (method == nil) then
        _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP")
    end
    request = nil
    local sendfile = require("send_file")

    print("before handle request")
    if (path == "/favicon.ico") then
        sendfile(c, "favicon.png")
    elseif (path == "/start_page.css") then
        sendfile(c, "start_page.css")
    elseif (path == "/start_page.js") then
        sendfile(c, "start_page.js")
    elseif (method == "POST" and path == "/settings") then
        bodyHandler = require("settings_handler")
        local _, _, body = string.find(request, "\r\n\r\n(.+)")
        if body then
            q(bodyHandler, c, request)
            bodyHandler = nil
        end
    elseif (method == "GET" and path == "/settings") then
        require("send_settings")(c)
    else
        sendfile(c, "start_page.html")
    end

    require("clear")()
end