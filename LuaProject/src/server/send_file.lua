return function(c, fname, cb)
    local send = require("sender")
    local fileBuffer = {}

    local function sbuff(c)
        if (#fileBuffer > 0) then
            local part = table.remove(fileBuffer, 1)
            print("part")
            send(c, part, sbuff)
        else
            print("file end")
            fileBuffer = nil
            if cb then
                cb(c)
            else
                c:close()
            end
        end
    end

    file.open(fname)
    local k, buf = pcall(file.read)
    while k and buf do
        fileBuffer[#fileBuffer + 1] = buf
        k, buf = pcall(file.read)
        if (not k) then print("bad bad") end
    end
    file.close()
    sbuff(c)
end
