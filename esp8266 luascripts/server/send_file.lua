return function(c, fname, cb)
local send = require("sender")
local f = require("fopen")
local function sfile(c)
    local buf = file.read()
    if buf then send(c, buf, sfile)
    else f.close() if cb then cb(c) else c:close() end end
end
f.open(fname,function() sfile(c) end)
end
