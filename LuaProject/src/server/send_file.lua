local c, fname, cb = ...

local fileBuffer = {}
local busyFileSend = false

file.open(fname)
local k, buf = pcall(file.read)
while k and buf do
    fileBuffer[#fileBuffer + 1] = buf
    k, buf = pcall(file.read)
    if (not k) then print("can not read file: ", fname) end
end
file.close()

local function sendProcess()
    if not busyFileSend then
        if (#fileBuffer > 0) then
            busyFileSend = true
            local part = table.remove(fileBuffer, 1)
            c:send(part)
            tmr.wdclr()
        else
            tmr.unregister(3)
            if cb then
                cb(c)
            else
                c:close()
            end
        end
    end
end

c:on("sent", function() busyFileSend = false end)
tmr.register(3, 50, tmr.ALARM_AUTO, sendProcess)
tmr.start(3)
