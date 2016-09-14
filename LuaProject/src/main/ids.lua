return function(cb)
    local CFG = _G["cfg"]
    if wifi.sta.status() == wifi.STA_GOTIP then
        http.get("http://" .. CFG.ip .. ":" .. CFG.port .. "/guestAuth/app/rest/buildTypes",
            "Accept: application/json\r\n",
            function(code, data)
                local function safe(code, data)
                    local st = _C.OK
                    if (code ~= 200) then
                        if (code < 0) then st = _C.C_ERR else st = _C.R_ERR end
                    else
                        local jIds = cjson.decode(data)
                        data = nil

                        local newIds = {}
                        local ind = 1;
                        for _, v in pairs(jIds.buildType) do
                            newIds[ind] = v.id
                            ind = ind + 1;
                        end
                        jIds = nil

                        file.open("ids")
                        local notParsedIds = file.read()
                        file.close()

                        local isNew = false
                        if notParsedIds then
                            local oldIds = cjson.decode(notParsedIds)
                            notParsedIds = nil
                            for i, _ in pairs(newIds) do
                                if newIds[i] ~= oldIds[i] then isNew = true break end
                            end
                            oldIds = nil
                        else
                            isNew = true
                        end

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

                local res = pcall(safe, code, data)
                if (not res) then
                    cb(_C.P_ERR)
                end
            end)
    else
        cb(_C.WIFI_ERR)
    end
end

