local content = {}
file.open("ids")
local buf = file.read()
while buf do
    content[#content + 1] = buf
    buf = file.read()
end
file.close()
local ids = {}
for id in table.concat(content):gmatch("\"(.-)\"") do
    ids[#ids + 1] = id
end
return ids