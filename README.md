# esp_mqtt_lcd

ESP8266 displaying mqtt messages on a Nokia 5110 LCD

I'm pulling in several git subtree modules :
* [tuanpmt's exellent mqtt project: esp_mqtt](https://github.com/tuanpmt/esp_mqtt) 
* [esp8266_pcd8544](https://github.com/eadf/esp8266_pcd8544) the lcd driver
* [esp8266_easygpio](https://github.com/eadf/esp8266_easygpio) makes it easy to change GPIO pins
* [esp8266_stdout](https://github.com/eadf/esp8266_stdout) alternative UART implementation (required if you want to connect the lcd with only 3 pins) 

Good news, the interface no longer requires 5 available GPIO outputs so an ESP-01 will indeed work. (But only if the RX pin of the esp is used.)

##Usage
To use this mqtt enabled LCD you can send text messages to these topics:
* /lcd0
* /lcd1
* /lcd2
* /lcd3
* /lcd4
* /lcd5

Representing each row of the display.

The LCD is also listening to these topics:
* /lcd/clearscreen
* /lcd/contrast

You can also send messages to topics that are unique to each *esp*, look at the debug console for more info.

### Pin configuraton

This is how the code is hooked up by default:

PCD8544| ESP8266
-------|------------------
RST Pin 1 | GPIO4
CE  Pin 2 | GPIO5
DC  Pin 3 | GPIO12
Din Pin 4 | GPIO13
Clk Pin 5 | GPIO14

Some ESP-12 have GPIO4 & GPIO5 reversed.

The RST pin is optional, set it to a negative value and tie PCD8544 reset to ESP reset via a resistor.

The CE pin is optional, set it to a negative value and tie PCD8544 CE pin to GND via a resistor.

All of the pins are configurable, you just set the pins you want to use in the setting struct.

The makefile is copied from [esp_mqtt.](https://github.com/tuanpmt/esp_mqtt)

###Building and installing:

First you need to install the sdk and the easy way of doing that is to use [esp_open_sdk.](https://github.com/pfalcon/esp-open-sdk)

You can put that anywhere you like (/opt/local/esp-open-sdk, /esptools etc etc)

Then you could create a small ```setenv.sh``` file, containing the location of your newly compiled sdk and other platform specific info;
```
export SDK_BASE=/opt/local/esp-open-sdk/sdk
export PATH=${SDK_BASE}/../xtensa-lx106-elf/bin:${PATH}
export ESPPORT=/dev/ttyO0  
```
(or setup your IDE to do the same)

You will have to edit the ```include/user_config.h``` file to suit your WiFi and mqtt settings. Alternatively you can copy ```include/user_config.h``` into ```localinclude/user_config.h``` and git will not bother you about modified files.

To make a clean build, flash and connect to the esp console you just do this in a shell:
```
source setenv.sh # This is only needed once per session
make clean && make test
```

You won't be needing esptool, the makefile only uses esptool.py (provided by esp-open-sdk)

I have tested this with sdk 1.5.2, v0.9.5 and v0.9.4 (linux & mac)
