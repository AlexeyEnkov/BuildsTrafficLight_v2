function v(){function g(a){d.getElementById("err").className=a?"show":""}function q(){for(var a in c)c.hasOwnProperty(a)&&(d.getElementById(a).className=c[a]?"act":"")}function r(a){Array.prototype.slice.call(d.querySelectorAll("input")).forEach(function(b){b.disabled=a});t.className=a?"dis":""}function h(){f=!1;r(!1);k.className=""}function p(){f=!0;g(!1);r(!0);k.className="process"}function u(){p();fetch("/settings").then(function(a){return a.json()}).then(function(a){n=a.ids;a=a.data;var b=n,e=
    a.cfg.ignoredIds,f=d.getElementById("idscont");f.innerHTML="";for(var l=0;l<b.length;l++){var g=d.createElement("label");g.innerHTML="<div>"+b[l]+"</div><input name="+b[l]+" type='checkbox' "+(e&&-1!=e.indexOf(b[l])?"checked='y'":"")+"/>";g.title=b[l];f.appendChild(g)}b=a.cfg;m("ssid",b.ssid);m("ip",b.ip);m("port",b.port);b.bright&&(m("red",b.bright.r),m("yellow",b.bright.y),m("green",b.bright.g));d.querySelector("input[name='sound']").checked=b.sound;d.getElementById("ip").textContent="Wifi: "+(a.ownIp?
    "connected. Local ip: "+a.ownIp:"not connected.");b=d.getElementById("cid");b.textContent="";for(var k in c)c.hasOwnProperty(k)&&(c[k]=!1);switch(a.status){case 1:c.g=!0;break;case 3:c.r=!0;c.y=!0;break;case 2:c.r=!0,b.textContent="Failed build: "+a.targetId}q();h()})["catch"](function(a){h();g(!0);console.error(a)})}function w(){p();fetch("/lights",{method:"POST",body:JSON.stringify(c)}).then(function(){h()})["catch"](function(a){console.error(a);h()})}function x(){p();fetch("/settings",{method:"POST",
    body:JSON.stringify(y())}).then(function(a){console.log(a.status);return a.json()}).then(function(a){h();console.log(a)})["catch"](function(a){h();g(!0);console.error(a)})}function y(){var a={};a.ssid=e("ssid").value;a.pass=e("pass").value;a.ip=e("ip").value;a.port=e("port").value;a.sound=e("sound").checked;a.bright={};a.bright.r=e("red").value;a.bright.y=e("yellow").value;a.bright.g=e("green").value;a.ignoredIds=[];for(var b=0;b<n.length;b++){var c=n[b];e(c).checked&&a.ignoredIds.push(c)}return a}
    function m(a,b){var c=e(a);c&&(c.value=b)}function e(a){return d.querySelector("input[name='"+a+"']")}var d=document,n=[],c={r:!1,y:!1,g:!1},f=!1,t=d.getElementById("save"),k=d.getElementById("refresh");k.onclick=function(){f||u()};t.onclick=function(){f||x()};d.getElementById("trl").onclick=function(a){a=a.target.id;c.hasOwnProperty(a)&&!f&&(c[a]=!c[a],w(),q())};Array.prototype.slice.call(d.querySelectorAll("#bright input")).forEach(function(a){a.onblur=function(a){return function(){100<a.value&&
    (a.value=100);0>a.value&&(a.value=0)}}(a)});return{update:u}}window.onload=function(){v().update()};