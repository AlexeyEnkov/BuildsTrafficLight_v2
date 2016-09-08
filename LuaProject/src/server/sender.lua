return function(c, data, cb)
    c:on("sent", function(c)
        print("data sended")
        if cb then
            cb(c)
        else
            c:close()
        end
    end)
    print("start send")
    c:send(data)
end
