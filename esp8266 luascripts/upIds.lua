http.get(
"http://".._G["ip"]..":".._G["port"].."/guestAuth/app/rest/buildTypes",
"Accept: application/json\r\n",
function(code, data)
if (code ~= 200) then
  print("C_ERR")
else
  ok, json = pcall(cjson.decode, data)
  if ok then
     file.open("bId", "r")
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
         file.open("bId", "w")
         for k,v in pairs(json.buildType) do 
            fLine = file.writeline(v.id)
         end
         file.close()
     end
     print("OK")
  else
     print("P_ERR")
  end
end
end)
