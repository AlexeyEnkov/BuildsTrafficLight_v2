return function(rec)
    local s = require("send_resp")
    if wifi.sta.status() == 5 then s("OK")
    else
        if not rec then s("ERR")
        else
            local function cb(r)
            s(r) wifi.sta.eventMonStop(1)
            end
            wifi.sta.eventMonReg(wifi.STA_GOTIP, function() cb("OK") end)
            wifi.sta.eventMonReg(wifi.STA_APNOTFOUND, function() cb("ERR") end)
            wifi.sta.eventMonReg(wifi.STA_FAIL, function() cb("ERR") end)
            wifi.sta.eventMonReg(wifi.STA_WRONGPWD, function() cb("ERR") end)
            wifi.sta.eventMonStart()
            wifi.sta.config(_G["cfg"].ssid, _G["cfg"].pass)
            wifi.sta.connect()
        end
    end
end
