_M_LOCK = true

if wifi.sta.status() ~= wifi.STA_GOTIP and not tmr.state(_C.WIFI_TMR) then
    loadScript("wifi_con")()
    print("reconnect from main")
end

local s = loadScript("send_resp")

local function onEnd()
    loadScript("clear")()
    _M_LOCK = false -- it is important to reset this flag
end

local function errCb(st)

    if (node.heap() < 20000 and st == _C.P_ERR) then
        print("need memory", st)
        node.restart()
    end

    if (st == _C.WIFI_ERR or wifi.sta.status() ~= wifi.STA_GOTIP) then
        s("L3")
    elseif st == _C.C_ERR then
        s("L1")
    elseif st == _C.R_ERR then
        s("L2")
    end

    onEnd()
end

local function onUpdStatus(st)
    local soundNum;
    local lightNum = 0;
    if st == _C.B_SUCC then
        lightNum = 5;
        soundNum = 1;
    elseif st == _C.B_FAIL then
        lightNum = 4;
        soundNum = 2;
    else
        lightNum = 6;
    end

    local statusChanged = _G["lStatus"] ~= st;
    if (statusChanged and soundNum) then
        s("S" .. soundNum)
    end

    if (not _L_LOCK) then
        s("L" .. lightNum)
    end

    _G["lStatus"] = st
    onEnd()
end

local function onUpdateIdsCb(st)
    if st == _C.OK then
        require("status")(onUpdStatus, errCb)
    else
        _G["timeForNextUpdIds"] = 0;
        errCb(st)
    end
end

local timeForUpdIds = _G["timeForNextUpdIds"]
if not timeForUpdIds then timeForUpdIds = 0 end

local now = tmr.time() -- time in seconds
local step = 120; -- in seconds
local max = 2147483647;
if timeForUpdIds < now then
    local nextTime = 0;
    if (max - now) < step then
        nextTime = step - (max - now)
    else
        nextTime = now + step
    end
    _G["timeForNextUpdIds"] = nextTime
    require("ids")(onUpdateIdsCb)
    print("start update ids")
else
    onUpdateIdsCb(_C.OK)
end

