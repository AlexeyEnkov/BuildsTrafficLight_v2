local M={}
_G["fqueue"]={}
function M.open(name,cb,mode)
    if not mode then mode="r" end
    _G["fqueue"][#_G["fqueue"]+1]={n=name,m=mode,c=cb}
    if #_G["fqueue"]==1 then 
       file.open(name,mode)
       cb() 
    end
end

function M.close()
    file.close()
    table.remove(_G["fqueue"],1)
    if #_G["fqueue"]>0 then
        local nowExec = _G["fqueue"][1]
        file.open(nowExec.n,nowExec.m)
        nowExec.c()
    end
end

return M
