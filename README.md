# esp8266_easygpio
An easy way of setting up esp8266 GPIO pins.

I grew tired of juggling gpio pin numbers, gpio names and gpio functions. So i created this little helper library.

To setup a pin as a GPIO input you can now just do this:

```
#include "easygpio/easygpio.h"
...

uint8_t gpio_pin = 0;
EasyGPIO_PullStatus pullStatus = EASYGPIO_NOPULL;
EasyGPIO_PinMode pinMode = EASYGPIO_INPUT;
bool easygpio_pinMode(gpio_pin, pullStatus, pinMode);
```

Same thing with outputs:
```
uint8_t gpio_pin = 0;
EasyGPIO_PullStatus pullStatus = EASYGPIO_NOPULL;
EasyGPIO_PinMode pinMode = EASYGPIO_OUTPUT;
bool easygpio_pinMode(gpio_pin, pullStatus, pinMode);
```
pullStatus does not apply to output pins.

You might still need the gpio_name and func. No problem:
```
bool easygpio_getGPIONameFunc(uint8_t gpio_pin, uint32_t *gpio_name, uint8_t *gpio_func)
```

You can even setup an interrupt handler:
```
bool easygpio_attachInterrupt(uint8_t gpio_pin, EasyGPIO_PullStatus pullStatus, void (*interruptHandler)(void))
```

But you will still have to do this little dance in your interrupt handler code:
```

static void interrupt_handler(void) {
  uint32_t gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
  //clear interrupt status
  GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(my_interrupt_gpio_pin));
  ......
```

See an example [here](https://github.com/eadf/esp8266_digoleserial)

Use the methods and macros defined in gpio.h (from the sdk) to access the gpio values.
```
#include "gpio.h"
...
GPIO_OUTPUT_SET(gpio_no, bit_value) // GPIO_OUTPUT_SET(0,1) sets gpio0 to high
GPIO_DIS_OUTPUT(gpio_no) // GPIO_DIS_OUTPUT(2) turns off output on gpio2
GPIO_INPUT_GET(gpio_no) // GPIO_INPUT_GET(12) returns the input value of gpio12
```
##Required:

esp_iot_sdk_v0.9.4_14_12_19

I've successfully tested this with sdk v0.9.5 (linux makefile).
