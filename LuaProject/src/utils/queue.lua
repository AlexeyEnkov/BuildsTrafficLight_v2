return function(f, ...)
    local args = { ... }
    local function apply()
        f(unpack(args))
    end

    local res, _ = pcall(node.task.post, apply)
    if not res then
        print(_)
    end
    return res
end