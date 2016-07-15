return function(c, fname, cb)
local send = require("sender")
file.open(fname)
local function sfile(c)
    local buf = file.read()
    if buf then send(c, buf, sfile)
    else file.close() if cb then cb(c) else c:close() end end
end
sfile(c)
end
