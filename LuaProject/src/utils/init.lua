uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)
wifi.setmode(wifi.STATIONAP)
wifi.setphymode(wifi.PHYMODE_G)
wifi.sta.setmac("CE:A4:62:99:CF:75")
wifi.sta.autoconnect(0)
-- init ap with server
dofile("init_cfg.lua")

wifi.ap.config({ ssid = "trafficlight", pwd = "trafficlight" })
wifi.ap.setip({ ip = "192.168.1.1", netmask = "255.255.255.0", gateway = "192.168.1.1" })

require("wifi_con")()


dataPool = {}
local srv = net.createServer(net.TCP)
srv:listen(80, function(conn)
    require("clear")()
    collectgarbage("restart")
    conn:on("receive",
        function(conn, req)
            print("receive conn=", conn, "heap=", node.heap())
            dataPool[#dataPool + 1] = { c=conn, r=req }
            if (#dataPool == 1) then
                dataPool[1].c = nil
                dataPool[1].req = nil
                print(pcall(require("server"), conn, req))
            end
        end)
    conn:on("disconnection",
        function(c)
            collectgarbage("restart")
            print("close conn=", conn, "heap=", node.heap())
            table.remove(dataPool, 1)
            if (#dataPool > 0) then
                pcall(require("server"), dataPool[1].c, dataPool[1].r)
            end
        end)
end)

C = require("constants")
--init timer function for scheduling
--tmr.register(C.MAIN_TMR, 6000, tmr.ALARM_AUTO, require("main"))
--tmr.start(C.MAIN_TMR)
require("send_conf")()
local s = require("send_resp")
s("L0")
s("S0")
s = nil