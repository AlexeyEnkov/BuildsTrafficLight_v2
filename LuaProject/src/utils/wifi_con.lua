local scb, ecb = ...
if _WIFI_LOCK then
    return
end
_WIFI_LOCK = true
local function ercb()
    wifi.sta.eventMonStop(1)
    wifi.setmode(wifi.SOFTAP)
    if ecb then ecb() end
    print("errccb")
    _WIFI_LOCK = false
end

local function succb()
    wifi.sta.eventMonStop(1)
    if scb then scb() end
    print("succb")
    _WIFI_LOCK = false
end

wifi.sta.eventMonReg(wifi.STA_GOTIP, function() succb() end)
wifi.sta.eventMonReg(wifi.STA_APNOTFOUND, function() ercb() end)
wifi.sta.eventMonReg(wifi.STA_FAIL, function() ercb() end)
wifi.sta.eventMonReg(wifi.STA_WRONGPWD, function() ercb() end)

print("try connect")
wifi.setmode(wifi.STATIONAP)
wifi.sta.eventMonStart(300)
wifi.sta.config(_G["cfg"].ssid, _G["cfg"].pass)
wifi.sta.connect()