return function(rec)
    local s = require("send_resp")
    if wifi.sta.status() == 5 then s("OK")
    else
        if not rec then s("ERR")
        else
            require("wifi_con")(
                function() s("OK") end,
                function() s("ERR") end
            )
        end
    end
end
