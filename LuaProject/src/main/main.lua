return function()
    tmr.stop(C.MAIN_TMR)
    local s = require("send_resp")

    local function onEnd()
        require("clear")()
        tmr.start(C.MAIN_TMR)
    end

    local function errCb(st)
        if st == C.WIFI_ERR then
            s("L3")
        elseif st == C.ERR then
            s("L1")
        elseif st == C.ERR then
            s("L2")
        else
            -- P_ERR
            print(st)
        end

        onEnd()
    end

    local function onUpdStatus(st)
        -- check if changed
        if st == C.B_SUCC then
            s("L5")
        elseif st == C.B_FAIL then
            s("L4")
        else
            s("L6")
        end
        _G["lStatus"] = st

        onEnd()
    end

    local function onUpdateIdsCb(st)
        if st == C.OK then
            if not pcall(require("status"), onUpdStatus, errCb) then
                onEnd()
            end
        else
            errCb(st)
        end
    end

    local timeForUpdIds = _G["timeForNextUpdIds"]
    if not timeForUpdIds then timeForUpdIds = 0 end

    local now = tmr.now()
    local step = 1000 * 1000 * 30;
    local max = 2147483647;
    if timeForUpdIds < now then
        local nextTime = 0;
        if (max - now) < step then
            nextTime = step - (max - now)
        else
            nextTime = now + step
        end
        _G["timeForNextUpdIds"] = nextTime
        if not pcall(require("ids"), onUpdateIdsCb) then
            onEnd()
        end
        print("upIds")
    else
        onUpdateIdsCb(C.OK)
    end
end
