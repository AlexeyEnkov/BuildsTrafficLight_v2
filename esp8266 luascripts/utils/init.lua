uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)
wifi.setmode(wifi.STATIONAP)
wifi.sta.setmac("CE:A4:62:99:CF:75")
wifi.sta.autoconnect(0)
-- init ap with server
dofile("init_cfg.lua")

wifi.ap.config({ssid="trafficlight",pwd="trafficlight"})
wifi.ap.setip({ip="192.168.1.1", netmask="255.255.255.0", gateway="192.168.1.1"})

require("wifi_con")()

srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", require("server"))
end)
-- did not work mdns.register("t")

C = require("constants")
--require("send_resp")("OK")
--init timer function for scheduling
--tmr.register(2,2000,tmr.ALARM_AUTO, function() dofile("get_stat.lua") end)
--tmr.start(2)
