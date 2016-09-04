local s=require("send_resp")
if wifi.sta.status()==5 then
http.get(
"http://".._G["cfg"].ip..":".._G["cfg"].port.."/guestAuth/app/rest/buildTypes",
"Accept: application/json\r\n",
function(code, data)
    local st="OK"
    if (code ~= 200) then if(code<0) then s("C_ERR") else s("R_ERR") end
    else
      local ok, json = pcall(cjson.decode, data)
      data=nil
      if ok and json.buildType then
         local newIds = {}
         local ind = 1
         for _,v in pairs(json.buildType) do 
            newIds[ind]=v.id
            ind = ind+1
         end
         json=nil
         local f=require("fopen")
         local function updIds()
             local notParseIds = file.read()
             f.close()
             isNew = false
             if notParseIds then
                local k,oldIds= pcall(cjson.decode,notParseIds)
                if k then
                    for i,_ in pairs(newIds) do
                        if newIds[i] ~= oldIds[i] then isNew=true break end 
                    end
                    oldIds=nil
                else
                    isNew = true
                end
             else
                isNew=true
             end
             notParseIds=nil
             if isNew then
                local function saveIds()
                    local k, idsJson = pcall(cjson.encode,newIds)
                    if k then file.write(idsJson) end
                    idsJson = nil
                    f.close()
                end
                f.open("ids", saveIds,"w")
             end
             newIds=nil
             s("OK")
         end
         f.open("ids",updIds)  
      else
         s("P_ERR")
      end
    end
end)
else
    s("W_ERR")
end
