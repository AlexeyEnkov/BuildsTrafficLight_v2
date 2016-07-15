local module=...
local bodyHandler
return function(c,request)
    if bodyHandler then bodyHandler(c, request) bodyHandler=nil return end
    local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP")
    if(method == nil) then _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP") end
    local sender = require("sender")
    if(path=="/favicon.ico") then require("send_file")(c,"favicon.png") return end
    if(method == "POST" and path == "/settings") then
        bodyHandler = require("settings_handler")
        local _,_,body=string.find(request,"\r\n\r\n(.+)")
        if body then bodyHandler(c, request) bodyHandler=nil end
        return
    end
    require("start_page")(c)
    if package.loaded[module] then package.loaded[module]=nil end
end
