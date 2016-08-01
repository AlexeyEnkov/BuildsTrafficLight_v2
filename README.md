# BuildsTrafficLight_v2
Project for smart traffic light that is used for watch state of TeamCity builds statuses
RED light means that there is at least one fail build
RED + YELLOW light means that faild build at now trying to complete
GREEN light means that all builds are completed

When build is faild traffic light plays fail song "Mario death"
When all builds become ok traffic light plays good song "Mario wakeup"
On startup of trafficl light plays sound "Imperial Marsh" from Star Wars

For play sound and for control lamps of traffic light is used Arduino Leonardo that ommunicates with esp8266 wifi module that has NoduMCU firmware

Also arduino is a scheduler. It's means that arduino send commnad "get status" and wifi module send commands to teamcity server and return answer in simple form:
"SUCC", "FAIL", "RUN", "OK", "WIFI_ERR" etc.

Programm for wifi module wrote on Lua

Module has simple htpp server with one page web interface for smart control and configuring  traffic light.
For access to web server of traffic light there is ap (in wifi module) with ssid "trafficlight". Also it possible via local network if there is wifi connection to it 
