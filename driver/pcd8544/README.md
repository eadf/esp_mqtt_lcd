# esp8266_pcd8544
PCD8544 LCD driver for esp8266 (Nokia 5110 &amp; 3110 display)

This is a direct port of code found at [arduino playground.](http://playground.arduino.cc/Code/PCD8544)

This git repository now only contains the the driver, the example code that used to be here is now moved to [pdc8544_example.](https://github.com/eadf/esp8266_pcd8544_example)

Here is another example of how this module can be used: [esp_mqtt_lcd](https://github.com/eadf/esp_mqtt_lcd).

Good news, the interface no longer requires 5 available GPIO outputs so an ESP-01 will indeed work. (But only if the RX pin of the esp is used.)

The RST pin is optional, set it to a negative value and tie PCD8544 reset to ESP reset via a resistor.

The CE pin is optional, set it to a negative value and tie PCD8544 CE pin to GND via a resistor.

All of the pins are configurable, you just set the pins you want to use in the setting struct.

I have tested this with sdk v0.9.5 and v0.9.4 (linux & mac makefile)

