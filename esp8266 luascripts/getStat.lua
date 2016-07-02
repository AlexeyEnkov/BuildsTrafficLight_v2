file.open("bId")
local busy = false
local FAIL="FAIL"
local SUCC="SUCC"
local RUN="RUN"
local status=SUCC
tmr.register(
1,
1,
tmr.ALARM_AUTO,
function()
if busy then return end
local id = file.readline()
if status ~= FAIL and id then
    busy = true
    http.get(
    "http://".._G["ip"]..":".._G["port"].."/guestAuth/app/rest/buildTypes/id:"..string.sub(id, 1, #id -1).."/builds/?locator=count:2,running:any",
    "Accept: application/json\r\n",
    function(code, data)
        busy = false
        if (code ~= 200) then
          if code < 0 then print("C_ERR") else print("R_ERR") end
        else
          ok, json = pcall(cjson.decode, data)
          if ok then
            local len = #json.build
            if len > 0 then
                if (json.build[1]).status=="FAILURE" then status=FAIL
                else
                    if len >= 2 then
                        if (json.build[1]).state=="running" and (json.build[2]).status=="FAILURE" then
                            status=RUN
                        end
                    end
                end
            end  
            for k,v in pairs(json.build) do 
                --print(v.status, v.state)
            end
          else
            print("P_ERR", node.heap())
          end
        end
    end)
else
    _G["lastStat"]=status
    print("OK")
    print(status)
    file.close()
    tmr.unregister(1)
end 
end)
tmr.start(1)
