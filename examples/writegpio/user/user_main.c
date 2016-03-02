/*
 * Copyright (c) 2015, eadf (https://github.com/eadf)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of Redis nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <osapi.h>
#include <os_type.h>
#include "gpio.h"
#include "easygpio/easygpio.h"
#include "stdout/stdout.h"

#define SAMPLE_PERIOD 200 // 200 ms
static os_timer_t dht22_timer;
uint8_t pinsToTest[] = {0,2,4,5,12,13,14,15,16};
uint8_t pinsToTestLen = 9;

static void ICACHE_FLASH_ATTR
loop(void) {
  // set this shift-rotating pattern to anything you like
  static uint32_t shiftReg = 1;//0b101010101;
  uint8_t i=0;
  os_printf("Setting ");
  for (i=0; i<pinsToTestLen; i++) {
    uint8_t flag = (shiftReg >> i) & 0x1;
    os_printf("GPIO%d=%d", pinsToTest[i], flag);
    easygpio_outputSet(pinsToTest[i], flag);
    //easygpio_outputEnable(pinsToTest[i], flag);
    if(i<pinsToTestLen-1) {
      os_printf(", ");
    }
  }

  os_printf("\n");
  if (shiftReg & 0x1) {
    shiftReg |= 0b1000000000;
  }
  shiftReg = (shiftReg >> 1);
}

void ICACHE_FLASH_ATTR
setup(void) {
  uint8_t i=0;
  for (i=0; i<pinsToTestLen; i++) {
    os_printf("Setting gpio%d as output\n", pinsToTest[i]);
    easygpio_pinMode(pinsToTest[i], EASYGPIO_NOPULL, EASYGPIO_OUTPUT);
  }
  os_printf("Starting to test the gpio pin values:\n");
  os_timer_disarm(&dht22_timer);
  os_timer_setfn(&dht22_timer, (os_timer_func_t *)loop, NULL);
  os_timer_arm(&dht22_timer, SAMPLE_PERIOD, true);
}

void ICACHE_FLASH_ATTR
user_init(void)
{
  // Make uart0 work with just the TX pin. Baud:115200,n,8,1
  // The RX pin is now free for GPIO use.
  stdout_init();

  // turn off WiFi for this console only demo
  wifi_station_set_auto_connect(false);
  wifi_station_disconnect();

  gpio_init();
  os_timer_disarm(&dht22_timer);
  os_timer_setfn(&dht22_timer, (os_timer_func_t *)setup, NULL);
  os_timer_arm(&dht22_timer, 2000, false);
}
