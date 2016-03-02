#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

/* All of the mqtt settings are now moved to mqtt_config.h * */

// application configurations:
#define PCD8544_RESET_PIN 4  //-1; This pin is now optional.
                             //   Set the PCD8544_RESET_PIN to negative value to disable the pin.
                             //   If you do disable it, you must tie LCD reset pin to esp reset via resistor.
#define PCD8544_SCE_PIN   5  //-1; This pin is now optional.
                             //   Set PCD8544_SCE_PIN to negative value to disable the pin.
                             //   If you do disable it, you must tie LCD CE pin to GND via resistor.
                             //   dcPin, sdinPin and sclkPin can be used for other SPI devices if scePin is *NOT* disabled.
#define PCD8544_DC_PIN   12
#define PCD8544_SDIN_PIN 13
#define PCD8544_SCLK_PIN 14
#define PCD8544_CONTRAST 60 // the default contrast
#endif
