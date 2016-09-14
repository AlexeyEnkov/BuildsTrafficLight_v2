local c, data = ...

local sendfile = loadScript("send_file")
print("handle", data.path, data.method, data.body, c)

local path = data.path
local method = data.method
if (path == "/favicon.ico") then
    sendfile(c, "favicon.png")
elseif (path == "/start_page.css") then
    sendfile(c, "start_page.css")
elseif (path == "/start_page.js") then
    sendfile(c, "start_page.js")
elseif (method == "POST" and path == "/settings") then
    loadScript("settings_handler")(c, data.body)
elseif (method == "GET" and path == "/settings") then
    loadScript("send_settings")(c)
else
    sendfile(c, "start_page.html")
end