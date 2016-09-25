node.egc.setmode(node.egc.NOT_ACTIVE)
node.setcpufreq(node.CPU160MHZ)

uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)

wifi.setmode(wifi.STATIONAP)
--wifi.setmode(wifi.STATION)
wifi.setphymode(wifi.PHYMODE_G)
wifi.sta.setmac("CE:A4:62:99:CF:75")
wifi.sta.autoconnect(1)

-- precompile files (did not working)
--[[for k, v in pairs(file.list()) do
    local _, _, luaName = string.find(k, "(.+)%.lua")
    if luaName then
        if luaName ~= "init" then
            print("compile", k)
            node.compile(k)
            file.remove(k)
        end
    end
    --print("name:" .. k .. ", size:" .. v)
end]]
-- init ap with server
function loadScript(script)
    return assert(loadfile(script .. ".lua"))
end

_CP = {}
function cPoolSize()
    local ind = 0;
    for k, _ in pairs(_CP) do
        ind = ind + 1;
    end
    return ind
end

dofile("init_cfg.lua")
_C = require("constants")

_WIFI_LOCK = false
_M_LOCK = false
_L_LOCK = false

wifi.ap.config({ ssid = "trafficlight", pwd = "trafficlight" })
wifi.ap.setip({ ip = "192.168.0.1", netmask = "255.255.255.0", gateway = "192.168.0.1" })

loadScript("init_server")()

--init timer function for scheduling
_MAIN_CO = coroutine.create(function()
    while true do
        if (cPoolSize() == 0) then
            loadScript("main")()
        end
        coroutine.yield()
    end
end)
--6000
tmr.register(_C.MAIN_TMR, 6000, tmr.ALARM_AUTO, function() coroutine.resume(_MAIN_CO) end)

-- start connect to wifi
local function mainStart()
    coroutine.resume(_MAIN_CO)
end

loadScript("wifi_con")(mainStart, mainStart)

-- send initial values only if bootreason is power up
code, reason = node.bootreason()
if (1 == code and reason == 0) then
    loadScript("send_conf")()
    local s = loadScript("send_resp")
    s("L0")
    s("S0")
    s = nil
end