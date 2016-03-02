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

#define SAMPLE_PERIOD 750 // 750 ms
static os_timer_t loop_timer;
uint8_t pinsToTest[] = {0,2,3,4,5,12,13,14,15,16};
uint8_t pinsToTestLen = 10;

static void ICACHE_FLASH_ATTR
loop(void) {
  uint8_t i=0;
  for (i=0; i<pinsToTestLen; i++) {
    os_printf("GPIO%d==%d", pinsToTest[i], easygpio_inputGet(pinsToTest[i]));
    if(i<pinsToTestLen-1) {
      os_printf(", ");
    }
  }
  os_printf("\n");
}

void ICACHE_FLASH_ATTR
setup(void) {
  uint8_t i=0;
  for (i=0; i<pinsToTestLen; i++) {
    os_printf("Setting gpio%d as input\n", pinsToTest[i]);
    easygpio_pinMode(pinsToTest[i], EASYGPIO_NOPULL, EASYGPIO_INPUT);
  }
  os_printf("Starting to test the gpio pin values:\n");
  os_timer_disarm(&loop_timer);
  os_timer_setfn(&loop_timer, (os_timer_func_t *)loop, NULL);
  os_timer_arm(&loop_timer, SAMPLE_PERIOD, true);
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
  os_timer_disarm(&loop_timer);
  os_timer_setfn(&loop_timer, (os_timer_func_t *)setup, NULL);
  os_timer_arm(&loop_timer, 2000, false);
}
