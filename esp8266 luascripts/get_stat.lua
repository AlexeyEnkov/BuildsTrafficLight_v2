file.open("bId")
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
    busy = true
    http.get(
    "http://".._G["ip"]..":".._G["port"].."/guestAuth/app/rest/buildTypes/id:"..string.sub(id, 1, #id -1).."/builds/?locator=count:2,running:any",
    "Accept: application/json\r\n",
    function(code, data)
        busy = false
        if (code ~= 200) then if(code<0) then reqSt="C_ERR" else reqSt="R_ERR" end
        else
          ok, json = pcall(cjson.decode, data)
          if ok then
            local len = #json.build
            if len > 0 then
                if (json.build[1]).status=="FAILURE" then status=B_FAIL
                else
                    if len >= 2 then
                        if (json.build[1]).state=="running" and (json.build[2]).status=="FAILURE" then
                            status=B_RUN
                        end
                    end
                end
            end  
          else
            reqSt="P_ERR"
          end
        end
    end)
else
    _G["lastStat"]=status
    local sender = require("send_resp")
    sender(reqSt)
    if reqSt="OK" then sender(status) end
    file.close()
    tmr.unregister(1)
end 
end)
tmr.start(1)