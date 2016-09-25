local c, data, cb = ...
data = loadScript("decode")(data)
local k, lights = pcall(cjson.decode, data)
if k then
    local resp = "L7"
    resp = resp..(lights["r"] and "1" or "0")
    resp = resp..(lights["y"] and "1" or "0")
    resp = resp..(lights["g"] and "1" or "0")
    _L_LOCK = true
    tmr.alarm(_C.CL_TMR, 60000, tmr.ALARM_SINGLE, function() _L_LOCK = false end)
    loadScript("send_resp")(resp)
end
loadScript("sender")(c, "HTTP/1.0 200 OK", cb)

