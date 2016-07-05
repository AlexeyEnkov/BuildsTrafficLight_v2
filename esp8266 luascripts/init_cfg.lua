file.open("cfg")
repeat
fl=file.readline()
if fl then
ind=string.find(fl, '=')
_G[string.sub(fl, 1, ind-1)]=string.sub(fl, ind+1, #fl-1)
end
until not fl
file.close()