return function(scb,ecb)
function ercb()
    wifi.setmode(wifi.SOFTAP)
    if ecb then ecb() end
end
function succb()
    wifi.sta.eventMonStop(1)
    if scb then scb() end
end
wifi.setmode(wifi.STATIONAP)
wifi.sta.eventMonReg(wifi.STA_GOTIP, function() succb() end)
wifi.sta.eventMonReg(wifi.STA_APNOTFOUND, function() ercb() end)
wifi.sta.eventMonReg(wifi.STA_FAIL, function() ercb() end)
wifi.sta.eventMonReg(wifi.STA_WRONGPWD, function() ercb() end)
wifi.sta.eventMonStart()
wifi.sta.config(_G["cfg"].ssid, _G["cfg"].pass)
wifi.sta.connect()
end