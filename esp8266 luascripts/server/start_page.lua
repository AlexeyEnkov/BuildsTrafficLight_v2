module=...
return function(c)
local s = require("sender")

local function sendConf(c)
local cfg=_G["cfg"]
local dt = {}
dt.cfg={}
dt.cfg.ssid=cfg.ssid dt.cfg.ip=cfg.ip dt.cfg.port=cfg.port
dt.cfg.sound=cfg.sound dt.cfg.bright=cfg.bright
if #cfg.ignoredIds > 0 then dt.cfg.ignoredIds=cfg.ignoredIds end
dt.status=_G["lStatus"] dt.targetId=_G["targetId"]
dt.ownIp=wifi.sta.getip()
local ok, jsData = pcall(cjson.encode, dt)
if ok then
s(c,"var rawData='"..jsData.."';</script>")
else
s(c,"</script>")
end
end
local first=true;
local function sendId(c)
    if first then file.open("ids") end
    local id = file.readline()
    if id then
    id = string.sub(id, 1, #id -1)
    id = "'"..id.."'"
    if not first then id=","..id end
    first = false
    s(c, id, sendId)
    else
    file.close()
    s(c,"];", sendConf)
    end
end
require("send_file")(c, "start_page.html", function(c) s(c, "<script type='text/javascript'>var IDS = [", sendId) end)
if package.loaded[module] then package.loaded[module]=nil end
end
