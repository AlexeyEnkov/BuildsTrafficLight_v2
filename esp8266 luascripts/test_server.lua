http.get(
"http://".._G["ip"]..":".._G["port"].."/guestAuth/app/rest/buildTypes",
nil,
function(code, data)
local st
if (code ~= 200) then if(code<0) then st="C_ERR" else st="R_ERR" end
else st="OK"
end
require("send_resp")(st)
end)