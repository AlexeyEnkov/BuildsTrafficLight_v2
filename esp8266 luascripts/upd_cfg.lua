local module=_
return function(ssid,pass,ip,port)
file.open("cfg", "w")
file.writeline("ssid="..ssid)
file.writeline("pass="..pass)
file.writeline("ip="..ip)
file.writeline("port="..port)
file.close()
dofile("init_cfg.lua")
end