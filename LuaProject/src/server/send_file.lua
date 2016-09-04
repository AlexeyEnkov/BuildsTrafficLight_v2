return function(c, fname, cb)
    local send = require("sender")
    --local f = require("fopen")
    local function sfile(c)
        local k, buf = pcall(file.read)
        if k and buf then
            send(c, buf, sfile)
        else
            file.close()
            if cb then
                cb(c)
            else
                c:close()
            end
        end
    end
    file.open(fname)
    sfile(c)
    --f.open(fname, function() sfile(c) end)
end
