uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)
--wifi.setmode(wifi.STATIONAP)
wifi.setmode(wifi.STATION)
--wifi.setphymode(wifi.PHYMODE_G)
wifi.setphymode(wifi.PHYMODE_N)
wifi.sta.setmac("CE:A4:62:99:CF:75")
wifi.sta.autoconnect(0)
-- precompile files
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
dofile("init_cfg.lua")

wifi.ap.config({ ssid = "trafficlight", pwd = "trafficlight" })
wifi.ap.setip({ ip = "192.168.1.1", netmask = "255.255.255.0", gateway = "192.168.1.1" })

require("wifi_con")()

-- store CON, PATH, BODY
local srv = net.createServer(net.TCP)
srv:listen(80, function(c) pcall(require("server_listener"), c) end)

C = require("constants")
--init timer function for scheduling
--tmr.register(C.MAIN_TMR, 6000, tmr.ALARM_AUTO, require("main"))
--tmr.start(C.MAIN_TMR)
require("send_conf")()
local s = require("send_resp")
s("L0")
s("S0")
s = nil