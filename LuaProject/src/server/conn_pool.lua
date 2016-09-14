local m = {}
m.pool = {}
m.size = function()
    local ind = 0;
    for k, _ in pairs(m.pool) do
        ind = ind + 1;
    end
    return ind
end

m.get = function(c)
    return m.pool[c]
end

m.put = function(c, data)
    m.pool[c] = data
end

m.first = function()
    for c, _ in pairs(m.pool) do
        return c
    end
end
return m

