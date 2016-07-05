local module=_
return function(r) print("$"..r) --[[package.loaded[module]=nil]] module=nil end