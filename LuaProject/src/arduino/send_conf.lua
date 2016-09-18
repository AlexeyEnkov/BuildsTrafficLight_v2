local br = _G["cfg"].bright
local resp = ""
if br then
    resp = "br=r:" .. br.r .. ",y:" .. br.y .. ",g:" .. br.g .. ";"
end
if _G["cfg"].sound ~= nil then
    resp = resp .. "sound=" .. (_G["cfg"].sound and "1" or "0") .. ";"
end
loadScript("send_resp")("C" .. resp)

