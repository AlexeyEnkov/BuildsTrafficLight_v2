uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)
wifi.setmode(wifi.STATIONAP)
wifi.sta.setmac("CE:A4:62:99:CF:75")
-- init ap with server
dofile("init_cfg.lua")
require("send_resp")("OK")