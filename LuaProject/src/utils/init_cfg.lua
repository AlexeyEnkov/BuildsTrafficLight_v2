file.open("cfg")
fl = file.readline()
ok, res = pcall(cjson.decode, fl)
if ok then _G["cfg"] = res res = nil end
file.close()
