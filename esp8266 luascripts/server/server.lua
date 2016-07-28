local module=...
local bodyHandler
return function(c,request)
    --print("--receive--\n"..request.."\n--end receive--\n")
    if bodyHandler then bodyHandler(c, request) bodyHandler=nil return end
    local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP")
    if(method == nil) then _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP") end
    local sendfile = require("send_file")
    if (path=="/favicon.ico") then sendfile(c,"favicon.png")
    elseif (path=="/start_page.css") then sendfile(c,"start_page.css")
    elseif (path=="/start_page.js") then sendfile(c,"start_page.js")
    elseif (method == "POST" and path == "/settings") then
        bodyHandler = require("settings_handler")
        local _,_,body=string.find(request,"\r\n\r\n(.+)")
        if body then bodyHandler(c, request) bodyHandler=nil end
    elseif (method == "GET" and path == "/settings") then
        require("send_settings")(c)
    else sendfile(c,"start_page.html") end
    if package.loaded[module] then package.loaded[module]=nil end
end
