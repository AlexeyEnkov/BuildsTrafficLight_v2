local module=...
return function(c,data,cb)
local rData=require("decode")(data)
local _,_,rConf=string.find(rData, "config=(.+)")
local succ=false
if rConf then
    local k,nConf = pcall(cjson.decode,rConf) 
    if k then 
        local oldC = {}
        oldC.ssid=nConf.ssid
        if (nConf.pass and #nConf.pass >= 8) then oldC.pass=nConf.pass else oldC.pass=_G["cfg"].pass end
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
        _G["cfg"]=oldC
        k, serNCfg = pcall(cjson.encode, oldC)
        if k then
            file.open("cfg", "w")
            file.writeline(serNCfg)
            file.close()
            succ=true
        end
    end
end
if package.loaded[module] then package.loaded[module]=nil end

local snd=require("sender")
local redirectJs="<script type='text/javascript'>setTimeout(function(){window.location.href='/'},2000);</script>"
if succ then
snd(c,"<div>Saved</div>"..redirectJs, function(c) c:close() c:on("disconnection",function(c) wifi.sta.config(_G["cfg"].ssid, _G["cfg"].pass) end) end )
else
snd(c,"<div>Err</div>"..redirectJs)
end
end