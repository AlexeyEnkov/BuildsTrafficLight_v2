return function(c, data, cb)
    c:send(data);
    c:on("sent", function(c) if cb then cb(c) else c:close() end end)
end
