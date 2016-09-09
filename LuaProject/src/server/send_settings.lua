return function(c)
    local s = require("sender")

    local function sendConf(c)
        local cfg = _G["cfg"]
        local dt = {}
        dt.cfg = {}
        dt.cfg.ssid = cfg.ssid dt.cfg.ip = cfg.ip dt.cfg.port = cfg.port
        dt.cfg.sound = cfg.sound dt.cfg.bright = cfg.bright
        if (#cfg.ignoredIds > 0) then dt.cfg.ignoredIds = cfg.ignoredIds end
        dt.status = _G["lStatus"] dt.targetId = _G["targetId"]
        dt.ownIp = wifi.sta.getip()
        local ok, jsData = pcall(cjson.encode, dt)
        dt = nil
        if ok then
            s(c, "\"rawData\":" .. jsData .. "}")
            --jsData = nil
        else
            s(c, "\"rawData\":null}")
        end
    end

    local sf = require("send_file")
    local function sendId(c)
        sf(c, "ids"--[[, function(c) s(c, ",", sendConf) end]])
    end

    s(c, "HTTP/1.0 200 OK\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"IDS\":", sendId)
end
