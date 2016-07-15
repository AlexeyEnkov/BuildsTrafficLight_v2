file.open("ids")
local busy = false
B_FAIL="FAIL"
B_SUCC="SUCC"
B_RUN="RUN"
local status=B_SUCC
local reqSt="OK"
tmr.register(
1,
1,
tmr.ALARM_AUTO,
function()
if busy then return end
local id = file.readline()
if status ~= B_FAIL and id and reqSt=="OK" then
    id = string.sub(id, 1, #id -1)
    for i,v in pairs(_G["cfg"].ignoredIds) do
        if id==v then return end
    end
    
    busy = true
    http.get(
    "http://".._G["cfg"].ip..":".._G["cfg"].port.."/guestAuth/app/rest/buildTypes/id:"..id.."/builds/?locator=count:2,running:any",
    "Accept: application/json\r\n",
    function(code, data)
        busy = false
        if (code ~= 200) then if(code<0) then reqSt="C_ERR" else reqSt="R_ERR" end
        else
          ok, json = pcall(cjson.decode, data)
          if ok then
            local len = #json.build
            if len > 0 then
                if (json.build[1]).status=="FAILURE" then status=B_FAIL _G["targetId"]=id
                else
                    if len >= 2 then
                        if (json.build[1]).state=="running" and (json.build[2]).status=="FAILURE" then
                            status=B_RUN _G["targetId"]=id
                        end
                    end
                end
            end 
            json=nil 
          else
            reqSt="P_ERR"
          end
        end
    end)
else
    _G["lStatus"]=status
    local sender = require("send_resp")
    sender(reqSt)
    if reqSt=="OK" then sender(status) end
    collectgarbage();
    file.close()
    tmr.unregister(1)
end 
end)
tmr.start(1)
