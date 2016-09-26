file.open("cfg")
local cfg = file.readline()
local ok, res = pcall(cjson.decode, cfg)
cfg = nil;
file.close()
collectgarbage()
if ok then
    return res
end