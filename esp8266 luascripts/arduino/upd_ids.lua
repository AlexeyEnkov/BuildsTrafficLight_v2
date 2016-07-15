http.get(
"http://".._G["cfg"].ip..":".._G["cfg"].port.."/guestAuth/app/rest/buildTypes",
"Accept: application/json\r\n",
function(code, data)
local st="OK"
if (code ~= 200) then if(code<0) then st="C_ERR" else st="R_ERR" end
else
  ok, json = pcall(cjson.decode, data)
  if ok then
     file.open("ids", "r")
     isNew = false;
     for k,v in pairs(json.buildType) do 
        fL = file.readline()
        if fL == nil or (string.sub(fL, 1, #fL -1) ~= v.id) then
            isNew = true
            break
        end
     end
     if not isNew then isNew = file.readline() ~= nil end
     file.close()
     if(isNew) then
         file.open("ids", "w")
         for k,v in pairs(json.buildType) do 
            fLine = file.writeline(v.id)
         end
         file.close()
     end
     json=nil
  else
     st="P_ERR"
  end
end
require("send_resp")(st)
end)
