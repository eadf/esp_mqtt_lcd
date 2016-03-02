# esp8266_easygpio
An easy way of setting up esp8266 GPIO pins.

I grew tired of juggling gpio pin numbers, gpio names and gpio functions. So i created this little helper library.

To setup a pin as a GPIO input you can now just do this:

```
#include "easygpio/easygpio.h"
...
bool easygpio_pinMode(0, EASYGPIO_NOPULL, EASYGPIO_INPUT);
```

Same thing with outputs:
```
bool easygpio_pinMode(1, EASYGPIO_NOPULL, EASYGPIO_OUTPUT);
```
pullStatus does not apply to output pins.

You might still need the gpio_name and func. No problem:
```
bool easygpio_getGPIONameFunc(uint8_t gpio_pin, uint32_t *gpio_name, uint8_t *gpio_func)
```

You can even setup an interrupt handler:
```
bool easygpio_attachInterrupt(uint8_t gpio_pin, EasyGPIO_PullStatus pullStatus, void (*interruptHandler)(void* arg), void *interruptArg)
```

You can use the methods and macros defined in gpio.h (from the sdk) to access the 'standard' gpio pins (not GPIO16).
```
#include "gpio.h"
...
GPIO_OUTPUT_SET(gpio_no, bit_value) // GPIO_OUTPUT_SET(0,1) sets gpio0 to high
GPIO_DIS_OUTPUT(gpio_no) // GPIO_DIS_OUTPUT(2) turns off output on gpio2
GPIO_INPUT_GET(gpio_no) // GPIO_INPUT_GET(12) returns the input value of gpio12
```

To access *all* of the pins in an uniform way you can use 
```
uint8_t easygpio_inputGet(uint8_t gpio_pin);
void easygpio_outputSet(uint8_t gpio_pin, uint8_t value);
```
However, you should not rely on that these methods will change input/output status of a pin (like the gpio.h macros does).

e.g. if you call ```easygpio_outputSet``` on an input pin, the pin may or may not remain an input. This is because of performance and uniformity reasons. ```easygpio_outputSet(16,1)``` will never flip gpio16 to an output, and we can't have access methods with different semantics depending on pin number).

So if you need to change the input/output mode of a pin on the fly, you can use ```easygpio_outputDisable()``` or ```easygpio_outputEnable()```.

###Available pins

Pin number | Note
-----------|------
GPIO0 	   | this pin selects bootmode [(pull up for *normal* boot)](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process#esp-boot-modes)
GPIO1      | normally UART0 TX 
GPIO2 	   | this pin selects bootmode [(pull up for *normal* boot)](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process#esp-boot-modes)
GPIO3      | normally UART0 RX (you can use [stdout](https://github.com/eadf/esp8266_stdout) to use it as GPIO)
GPIO4      | sometimes mislabeled as GPIO5 (esp-12)
GPIO5      | sometimes mislabeled as GPIO4 (esp-12)
GPIO12     | 
GPIO13     |
GPIO14     |
GPIO15 	   | this pin selects bootmode [(pull down for *normal* boot)](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process#esp-boot-modes)
GPIO16      | requires easygpio_inputGet() & easygpio_outputSet() access methods (no interrupt on this pin)

All the GPIOs mentioned in ```easgle_soc.h``` are supported, but maybe we should not mess with the internal SPI pins for GPIO.

## Usage

The project has been designed for easy reuse, just create a folder with these files in it ([git subtree](http://blogs.atlassian.com/2013/05/alternatives-to-git-submodule-git-subtree) works great for that purpose). Then point your ```MODULES``` variable (or whatever subdirectory construct you use) in the ```Makefile``` to that folder . If you find yourself manually copying these individial .c and .h files - you're doing it wrong.

See an example on how this library can be used [here](https://github.com/eadf/esp8266_digoleserial), [here](https://github.com/eadf/esp_mqtt_lcd), [here](https://github.com/eadf/esp8266_ping), [here](https://github.com/eadf/esp_mqtt_ports) - bha.. practically all of my esp projects uses it.

## Todo
* Find the correct ```READ_PERI_REG()``` address for ```easygpio_inputGet()```, now it's simply using ```GPIO_INPUT_GET()```

## Required:

esp-open-sdk-1.5.2 or higher.

I've successfully tested this with sdk v0.9.5 (linux & mac).
