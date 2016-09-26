local cfg = loadScript("get_cfg")()
local br = cfg.bright
local resp = ""
if br then
    resp = "br=r:" .. br.r .. ",y:" .. br.y .. ",g:" .. br.g .. ";"
end
if cfg.sound ~= nil then
    resp = resp .. "sound=" .. (cfg.sound and "1" or "0") .. ";"
end
loadScript("send_resp")("C" .. resp)

