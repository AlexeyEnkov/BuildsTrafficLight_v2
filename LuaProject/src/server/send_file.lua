return function(c, fname, cb)
    local send = require("sender")
    local fileBuffer = {}

    --[[local ind = 1;
    local function sbuff(c)
            print("part")
        if (ind <= #fileBuffer) then
            local part = fileBuffer[ind] --table.remove(fileBuffer, 1)
            fileBuffer[ind] = nil
            ind = ind + 1;
            send(c, part, sbuff)
        else
            print("file end")
            fileBuffer = nil
            if cb then
                print(pcall(cb, c))
            else
                c:close()
            end
        end
    end]]

    print("file open: " .. fname)
    file.open(fname)
    local k, buf = pcall(file.read)
    while k and buf do
        fileBuffer[#fileBuffer + 1] = buf
        k, buf = pcall(file.read)
        if (not k) then print("bad bad") end
    end
    file.close()

    local busy = false
    c:on("sent", function() busy = false end)
    tmr.register(3, 10, tmr.ALARM_AUTO,
        function()
            if not busy then
                if (#fileBuffer > 0) then
                    busy = true
                    c:send(table.remove(fileBuffer, 1))
                else
                    tmr.unregister(3)
                    if cb then
                        cb(c)
                    else
                        c:close()
                    end
                end
            end
        end)
    tmr.start(3)
    --sbuff(c)
    print("file close: " .. fname)
    sbuff(c)
end
