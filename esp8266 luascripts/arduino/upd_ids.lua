local mod=...
return function()
http.get(
"http://".._G["cfg"].ip..":".._G["cfg"].port.."/guestAuth/app/rest/buildTypes",
"Accept: application/json\r\n",
function(code, data)
local st="OK"
if (code ~= 200) then if(code<0) then st="C_ERR" else st="R_ERR" end
else
  ok, json = pcall(cjson.decode, data)
  if ok then
     local f=require("fopen")
     local function checkIds()
         isNew = false
         for k,v in pairs(json.buildType) do 
            fL = file.readline()
            if fL == nil or (string.sub(fL, 1, #fL -1) ~= v.id) then
                isNew = true
                break
            end
         end
         if not isNew then isNew = file.readline() ~= nil end
         f.close()
         if isNew then
            local function wIds()
                for k,v in pairs(json.buildType) do 
                fLine = file.writeline(v.id)
                end
                f.close()
                json=nil     
            end
            f.open("ids",wIds, "w")  
         else json=nil end
     end
     f.open("ids",checkIds)  
  else
     st="P_ERR"
  end
end
require("send_resp")(st)
if package.loaded[mod] then package.loaded[mod]=nil end
end)
end
