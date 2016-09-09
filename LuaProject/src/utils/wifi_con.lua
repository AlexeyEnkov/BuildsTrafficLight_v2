return function(scb, ecb)
    local function ercb()
        wifi.setmode(wifi.SOFTAP)
        if ecb then ecb() end
        print("errccb")
        --tmr.alarm(C.WIFI_TMR, 1000, tmr.ALARM_SINGLE, conn)
    end

    local function succb()
        wifi.sta.eventMonStop(1)
        if scb then scb() end
        print("succb")
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

end