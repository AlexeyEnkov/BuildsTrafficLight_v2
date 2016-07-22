local M,module={},...

function M.open(fn)
if _G["fLock"] then tmr.alarm(2, 1000, tmr.ALARM_SINGLE, function() print("wait") M.open(fn) end) end
_G["fLock"]=true
file.open(fn)
end

function M.close()
file.close()
print("close")
_G["fLock"]=nil
end

return M