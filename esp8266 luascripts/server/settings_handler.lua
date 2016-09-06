local module=...
return function(c,data,cb)
local succ=false
local wifiChanged=false
if data then
    local k,nConf = pcall(cjson.decode,data) 
    if k then 
        local oldC = {}
        oldC.ssid=nConf.ssid
        if nConf.ssid ~= _G["cfg"].ssid then wifiChanged=true end
        if (nConf.pass and #nConf.pass >= 8) then wifiChanged=true oldC.pass=nConf.pass else oldC.pass=_G["cfg"].pass end
        oldC.ip=nConf.ip
        oldC.port=nConf.port
        local newBright={}
        if nConf.bright then
            local cbr = tonumber(nConf.bright.r)
            if cbr and cbr >=0 and cbr<=100 then newBright.r=cbr else newBright.r=0 end
            cbr = tonumber(nConf.bright.y)
            if cbr and cbr >=0 and cbr<=100 then newBright.y=cbr else newBright.y=0 end
            cbr = tonumber(nConf.bright.g)
            if cbr and cbr >=0 and cbr<=100 then newBright.g=cbr else newBright.g=0 end
            oldC.bright=newBright
        end
        oldC.sound=nConf.sound
        oldC.ignoredIds=nConf.ignoredIds
        nConf=nil
        _G["cfg"]=oldC
        k, serNCfg = pcall(cjson.encode, oldC)
        if k then
            require("fopen").open(
                "cfg",
                function()
                    file.writeline(serNCfg)
                    require("fopen").close()
                    succ=true
                    serCfg=nil
                end,
                "w")
        end
    end
end
if package.loaded[module] then package.loaded[module]=nil end

local snd=require("sender")
local headers = "HTTP/1.0 200 OK\r\nAccess-Control-Allow-Origin: *\r\n\r\n"
if succ then
snd(c,headers.."{\"result\": \"OK\"}", function(c) c:close() c:on("disconnection",function(c) if wifiChanged then require("wifi_con")() end end) end )
else
snd(c,headers.."{\"result\": \"Err\"}", function(c) c:close() end)
end
end
