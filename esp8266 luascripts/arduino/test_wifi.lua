local s = require("send_resp")
if wifi.sta.getip() then s("OK")
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
end