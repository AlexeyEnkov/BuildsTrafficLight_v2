var d = document;
function LTR(ids, data) {
    this.ids = ids;
    this.renderIds(ids, data["cfg"]["ignoredIds"]);
    this.fillForm(data["cfg"]);
    this.setUpInf(data);
    var s = this;
    d.getElementById("save").onclick = function () {
        s.save();
    };
}
LTR.prototype = {
    renderIds: function (ids, ignored) {
        var cont = d.getElementById("idscont");
        for (var i = 0; i < ids.length; i++) {
            var checked = ignored && ignored.indexOf(ids[i]) != -1;
            var idLbl = d.createElement("label");
            idLbl.innerHTML = "<div>" + ids[i] + "</div><input name=" + ids[i] + " type='checkbox' " + (checked ? "checked='y'" : "") + "/>";
            idLbl.title = ids[i];
            cont.appendChild(idLbl);
        }
    },
    getIn: function (name) {
        return d.querySelector("input[name='" + name + "']");
    },
    fillIn: function (name, val) {
        var inp = this.getIn(name);
        if (inp) inp.value = val;
    },
    fillForm: function (cfg) {
        this.fillIn("ssid", cfg["ssid"]);
        this.fillIn("ip", cfg["ip"]);
        this.fillIn("port", cfg["port"]);
        if (cfg["bright"]) {
            this.fillIn("red", cfg["bright"]["r"]);
            this.fillIn("yellow", cfg["bright"]["y"]);
            this.fillIn("green", cfg["bright"]["g"]);
        }
        d.querySelector("input[name='sound']").checked = cfg["sound"];
    },
    getCfg: function () {
        var cfg = {};
        cfg["ssid"] = this.getIn("ssid").value;
        cfg["pass"] = this.getIn("pass").value;
        cfg["ip"] = this.getIn("ip").value;
        cfg["port"] = this.getIn("port").value;
        cfg["sound"] = this.getIn("sound").checked;
        cfg["bright"] = {};
        cfg["bright"]["r"] = this.getIn("red").value;
        cfg["bright"]["y"] = this.getIn("yellow").value;
        cfg["bright"]["g"] = this.getIn("green").value;
        cfg["ignoredIds"] = [];
        for (var i = 0; i < this.ids.length; i++) {
            var id = this.ids[i];
            if (this.getIn(id).checked) {
                cfg["ignoredIds"].push(id);
            }
        }
        return cfg;
    },
    save: function () {
        fetch("/settings", {
            method: "POST",
            body: JSON.stringify(this.getCfg())
        })
            .then(
                function(response) {
                    console.log(response["status"]);
                    return response.json();
                }
            ).then(
            function(data) {
                console.log(data);
            }
        )
    },
    setUpInf: function (data) {
        d.getElementById("ip").textContent = "Wifi: " + (data["ownIp"] ? "connected. Local ip: " + data["ownIp"] : "not connected.");

        var r = d.getElementById("r");
        var y = d.getElementById("y");
        var g = d.getElementById("g");
        switch (data["status"]) {//TODO: constants (same as in constants.lua)
            case 1:
                g.className = "act";
                break;
            case 3:
                r.className = "act";
                y.className = "act";
                break;
            case 2:
                r.className = "act";
                d.getElementById("cid").textContent = "Failed build: " + data["targetId"];
                break;
        }
    }
};

window.onload = function() {
    fetch("/settings")
        .then(
            function(response) {
                console.log(response["status"]);
                return response.json();
            }
        )
        .then(
            function(data) {
                console.log(data);
                new LTR(data["IDS"],data["rawData"]);
            }
        )
};
