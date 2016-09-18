tmr.stop(_C.MAIN_TMR)
_MAIN_LOCK = true

if wifi.sta.status() ~= wifi.STA_GOTIP then
    loadScript("wifi_con")()
end

local s = loadScript("send_resp")

local function onEnd()
    loadScript("clear")()
    tmr.start(_C.MAIN_TMR)
    _MAIN_LOCK = false
end

local function errCb(st)

    if (node.heap() < 20000) then
        node.restart()
    end

    if st == _C.WIFI_ERR then
        s("L3")
    elseif st == _C.C_ERR then
        s("L1")
    elseif st == _C.R_ERR then
        s("L2")
    else
        -- P_ERR
        print(st)
        node.restart()
    end

    onEnd()
end

local function onUpdStatus(st)
    -- TODO check if status changed and change sound
    local statusChanged = _G["lStatus"] ~= st;
    if st == _C.B_SUCC then
        s("L5")
        if statusChanged then
            s("S1")
        end
    elseif st == _C.B_FAIL then
        s("L4")
        if statusChanged then
            s("S2")
        end
    else
        s("L6")
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
local step = 60;
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
    print("upIds")
else
    onUpdateIdsCb(_C.OK)
end

