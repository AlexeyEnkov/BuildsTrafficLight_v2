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
            s(c, "var rawData='" .. jsData .. "';</script>")
            jsData = nil
        else
            s(c, "</script>")
        end
    end

    local first = true;
    local f = require("fopen")
    local sf = require("send_file")
    local function sendId(c)
        sf(c, "ids", function(c) s(c, ";", sendConf) end)
    end

    sf(c, "start_page.html", function(c) s(c, "<script type='text/javascript'>var IDS = ", sendId) end)
end
