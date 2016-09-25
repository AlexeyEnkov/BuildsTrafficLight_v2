"use strict";
function LTR() {
    var d = document;
    var moduleContent = '';
    var ids = [];
    var activeLight = {
        "r": false,
        "y": false,
        "g": false
    };
    var processed = false;

    var getElemById = function (id) {
        return d.getElementById(id);
    };

    var querySelectAll = function (query) {
        return Array.prototype.slice.call(d.querySelectorAll(query))
    };

    var saveBtn = getElemById("save");
    var refreshBtn = getElemById("refresh");
    refreshBtn.onclick = function () {
        if (!processed)update()
    };
    saveBtn.onclick = function () {
        if (!processed)save()
    };
    getElemById("trl").onclick = function (e) {
        var id = e.target.id;
        if (activeLight.hasOwnProperty(id) && !processed) {
            activeLight[id] = !activeLight[id];
            sendLights();
            activateLights();
        }
    };

    querySelectAll("#bright input").forEach(function (inp) {
        inp.onblur = function (inp) {
            return function () {
                if (inp.value > 100) {
                    inp.value = 100;
                }
                if (inp.value < 0) {
                    inp.value = 0;
                }
            }
        }(inp);
    });

    var renderIds = function (ids, ignored) {
        var cont = getElemById("idscont");
        cont.innerHTML = "";
        for (var i = 0; i < ids.length; i++) {
            var checked = ignored && ignored.indexOf(ids[i]) != -1;
            var idLbl = d.createElement("label");
            idLbl.innerHTML = "<div>" + ids[i] + "</div><input name=" + ids[i] + " type='checkbox' " + (checked ? "checked='y'" : "") + "/>";
            idLbl.title = ids[i];
            cont.appendChild(idLbl);
        }
    };

    var getInput = function (name) {
        return d.querySelector("input[name='" + name + "']");
    };
    var fillInput = function (name, val) {
        var inp = getInput(name);
        if (inp) inp.value = val;
    };
    var fillForm = function (cfg) {
        fillInput("ssid", cfg["ssid"]);
        fillInput("ip", cfg["ip"]);
        fillInput("port", cfg["port"]);
        if (cfg["bright"]) {
            fillInput("red", cfg["bright"]["r"]);
            fillInput("yellow", cfg["bright"]["y"]);
            fillInput("green", cfg["bright"]["g"]);
        }
        d.querySelector("input[name='sound']").checked = cfg["sound"];
    };

    var getCfg = function () {
        var cfg = {};
        cfg["ssid"] = getInput("ssid").value;
        cfg["pass"] = getInput("pass").value;
        cfg["ip"] = getInput("ip").value;
        cfg["port"] = getInput("port").value;
        cfg["sound"] = getInput("sound").checked;
        cfg["bright"] = {};
        cfg["bright"]["r"] = getInput("red").value;
        cfg["bright"]["y"] = getInput("yellow").value;
        cfg["bright"]["g"] = getInput("green").value;
        cfg["ignoredIds"] = [];
        for (var i = 0; i < ids.length; i++) {
            var id = ids[i];
            if (getInput(id).checked) {
                cfg["ignoredIds"].push(id);
            }
        }
        return cfg;
    };

    var save = function () {
        onStartUpdate();
        fetch("/settings", {
            method: "POST",
            body: JSON.stringify(getCfg())
        })
            .then(
                function (response) {
                    console.log(response["status"]);
                    return response.json();
                }
            ).then(
            function (data) {
                onEndUpdate();
                console.log(data);
            })
            .catch(function (err) {
                onEndUpdate();
                showErr(true);
                console.error(err);
            });
    };

    var setupData = function (data) {
        getElemById("ip").textContent = "Wifi: " + (data["ownIp"] ? "connected. Local ip: " + data["ownIp"] : "not connected.");
        var failedIds = getElemById("cid");
        failedIds.textContent = "";
        for (var l in activeLight) {
            if (activeLight.hasOwnProperty(l))
                activeLight[l] = false;
        }
        switch (data["status"]) {//TODO: constants (same as in constants.lua)
            case 1:
                activeLight["g"] = true;
                break;
            case 3:
                activeLight["r"] = true;
                activeLight["y"] = true;
                break;
            case 2:
                activeLight["r"] = true;
                failedIds.textContent = "Failed build: " + data["targetId"];
                break;
        }
        activateLights();
    };

    var sendLights = function () {
        onStartUpdate();
        fetch("/lights", {
            method: "POST",
            body: JSON.stringify(activeLight)
        }).then(function () {
            onEndUpdate();
        }).catch(function (err) {
            console.error(err);
            onEndUpdate();
        });
    };

    var update = function () {
        onStartUpdate();
        fetch("/settings")
            .then(
                function (response) {
                    return response.json();
                }
            )
            .then(
                function (resp) {
                    ids = resp["ids"];
                    var data = resp["data"];
                    renderIds(ids, data["cfg"]["ignoredIds"]);
                    fillForm(data["cfg"]);
                    setupData(data);
                    onEndUpdate();
                }
            )
            .catch(
                function (err) {
                    onEndUpdate();
                    showErr(true);
                    console.error(err);
                }
            );
    };

    var onStartUpdate = function () {
        processed = true;
        showErr(false);
        onOffControls(true);
        refreshBtn.className = "process";
    };
    var onEndUpdate = function () {
        processed = false;
        onOffControls(false);
        refreshBtn.className = "";
    };

    var onOffControls = function (isOff) {
        querySelectAll('input')
            .forEach(function (el) {
                el.disabled = isOff;
            });
        saveBtn.className = isOff ? "dis" : "";
    };

    var activateLights = function () {
        for (var l in activeLight) {
            if (activeLight.hasOwnProperty(l))
                getElemById(l).className = activeLight[l] ? "act" : "";
        }
    };

    var showErr = function (isShow) {
        getElemById("err").className = isShow ? "show" : "";
    };


    return {
        update: update
    }
}

window.onload = function () {
    var ltr = LTR();
    ltr.update();
};
