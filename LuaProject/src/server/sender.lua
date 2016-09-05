return function(c, data, cb)
    c:on("sent", function(c)
        if cb then
            cb(c)
        else
            c:close()
        end
    end)
    require("queue")(function(d) c:send(d) end, data)
end
