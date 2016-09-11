return function(c, data)
    --print(request)
    local sendfile = require("send_file")

    print("before handle request")
    local path = data.path
    local method = data.method
    if (path == "/favicon.ico") then
        sendfile(c, "favicon.png")
    elseif (path == "/start_page.css") then
        sendfile(c, "start_page.css")
    elseif (path == "/start_page.js") then
        sendfile(c, "start_page.js")
    elseif (method == "POST" and path == "/settings") then
        require("settings_handler")(c, data.body)
    elseif (method == "GET" and path == "/settings") then
        require("send_settings")(c)
    else
        sendfile(c, "start_page.html")
    end
    require("clear")()
end