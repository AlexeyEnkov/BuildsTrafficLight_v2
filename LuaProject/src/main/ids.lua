return function(cb)
    local CFG = loadScript("get_cfg")()
    if wifi.sta.status() == wifi.STA_GOTIP then
        http.get("http://" .. CFG.ip .. ":" .. CFG.port .. "/guestAuth/app/rest/buildTypes",
            "Accept: application/json\r\n",
            function(code, data)
                local function safe(code, data)
                    local st = _C.OK
                    if (code ~= 200) then
                        if (code < 0) then
                            st = _C.C_ERR
                        else
                            st = _C.R_ERR
                        end
                    else
                        local newIds = {}
                        for id in data:gmatch("\"id\":\"(.-)\"") do
                            newIds[#newIds + 1] = id
                        end
                        data = nil

                        local isNew = false
                        local oldIds = loadScript("get_ids")()
                        if #newIds == #oldIds then
                            for i, _ in pairs(newIds) do
                                if newIds[i] ~= oldIds[i] then isNew = true break end
                            end
                        else
                            isNew = true
                        end
                        oldIds = nil

                        if isNew then
                            local idsJson = cjson.encode(newIds)
                            newIds = nil
                            file.open("ids", "w")
                            file.write(idsJson)
                            file.close()
                            idsJson = nil
                        end
                    end
                    cb(st)
                end

                safe(code, data)
--                local res = pcall(safe, code, data)
--                if (not res) then
--                    cb(_C.P_ERR)
--                end
            end)
    else
        cb(_C.WIFI_ERR)
    end
end

