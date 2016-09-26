local c, data, cb = ...

local succ = false
local wifiChanged = false

data = loadScript("decode")(data)
if data then
    local k, updConf = pcall(cjson.decode, data)
    if k then
        local newConf = {}
        newConf.ssid = updConf.ssid

        local cfg = loadScript("get_cfg")()
        local oldSsid = cfg.ssid
        local oldPass = cfg.pass
        cfg = nil
        if updConf.ssid ~= oldSsid then
            wifiChanged = true
        end
        if (updConf.pass and #updConf.pass >= 8) then
            wifiChanged = true newConf.pass = updConf.pass else newConf.pass = oldPass
        end
        newConf.ip = updConf.ip
        newConf.port = updConf.port
        local newBright = {}
        if updConf.bright then
            local cbr = tonumber(updConf.bright.r)
            if (cbr and (cbr >= 0) and cbr <= 100) then
                newBright.r = cbr else newBright.r = 0;
            end
            cbr = tonumber(updConf.bright.y)
            if (cbr and (cbr >= 0) and cbr <= 100) then
                newBright.y = cbr else newBright.y = 0;
            end
            cbr = tonumber(updConf.bright.g)
            if (cbr and (cbr >= 0) and cbr <= 100) then
                newBright.g = cbr else newBright.g = 0;
            end
            newConf.bright = newBright
        end
        newConf.sound = updConf.sound
        newConf.ignoredIds = updConf.ignoredIds
        updConf = nil

        local k, serNCfg = pcall(cjson.encode, newConf)
        if k then
            file.open("cfg", "w")
            if pcall(file.writeline, serNCfg) then
                succ = true
            end
            file.close()
            serNCfg = nil
        end
    end
end

local snd = loadScript("sender")
local headers = "HTTP/1.0 200 OK\r\nAccess-Control-Allow-Origin: *\r\n\r\n"
if succ then
    loadScript("send_conf")()
    snd(c, headers .. "{\"result\": \"OK\"}", function(c)
        if wifiChanged then
            loadScript("wifi_con")()
        end
        if cb then cb(c)
        else c:close() end
    end)
else
    snd(c, headers .. "{\"result\": \"Err\"}", cb)
end
