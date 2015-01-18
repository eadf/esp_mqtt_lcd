# esp8266_pcd8544
PCD8544 LCD driver for esp8266 (Nokia 5110 &amp; 3110 display)

This is a direct port of code found at [arduino playground.](http://playground.arduino.cc/Code/PCD8544)

The interface requires 5 available GPIO outputs so an ESP-01 will not work. 

This is how the code is hooked up:

PCD8544| ESP8266
-------|------------------
RST Pin 1 | GPIO4
CE  Pin 2 | GPIO5
DC  Pin 3 | GPIO12
Din Pin 4 | GPIO13
Clk Pin 5 | GPIO14

 
Some ESP-12 have GPIO4 & GPIO5 reversed.

I don't know if it is required but i put 1KΩ resistors on each gpio pin, and it does not seem to cause any problems. 
