local c, data = ...

print("handle", data.path, data.method, data.body, c)

local path = data.path

if not path then c:close() return end

local method = data.method
local okResp = "HTTP/1.0 200 OK\r\nCache-Control:max-age=604800\r\n\r\n" -- max-age=604800

local sfile = loadScript("send_file")
--[[local function sfile(c, name)
    return function() loadScript("send_file")(c, name) end
end]]

local sender = loadScript("sender")
if (path == "/favicon.ico") then
    --sender(c, okResp, sfile(c, "favicon.png"))
    sfile(c, "favicon.png")
elseif (path == "/start_page.css") then
    --sender(c, okResp, sfile(c, "start_page.css"))
    sfile(c, "start_page.css")
elseif (path == "/start_page.js") then
    --sender(c, okResp, sfile(c, "start_page.js"))
    sfile(c, "start_page.js")
elseif (method == "POST" and path == "/settings") then
    loadScript("settings_handler")(c, data.body)
elseif (method == "GET" and path == "/settings") then
    loadScript("send_settings")(c)
else
    --sender(c, okResp, sfile(c, "start_page.html"))
    sfile(c, "start_page.html")
end