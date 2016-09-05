return function()
    for i, v in pairs(package.loaded) do
        package.loaded[i] = nil
    end
end