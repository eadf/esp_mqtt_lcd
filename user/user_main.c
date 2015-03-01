/* main.c -- MQTT client example
 *
 * Copyright (c) 2014-2015, Tuan PM <tuanpm at live dot com>
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
#include "ets_sys.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "stdout/stdout.h"
#include "mem.h"
#include "pcd8544/pcd8544.h"
#include "user_config.h"

static uint8_t openhardware_logo[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xe0,0xe0,0xe0,0xc0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xe0,0xe0,0xe0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1e,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0xc0,0xc0,0xe0,0xe0,0xe0,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1f,0x1f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x1f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0xe0,0xe0,0xe0,0xc0,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x7f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe1,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x1e,0x00,0x00,0x00,0x00,0x00,0x06,0x1e,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcf,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x1f,0x3f,0x7f,0xff,0xff,0xff,0x7f,0x7f,0x3f,0x3f,0x1f,0x3f,0x3f,0x3f,0x0f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0f,0x3f,0x3f,0x3f,0x1f,0x3f,0x3f,0x7f,0xff,0xff,0xff,0xff,0x3f,0x3f,0x1e,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static PCD8544_Settings pcd8544_settings;

#define user_procTaskPeriod      1000
static volatile os_timer_t lcd_timer;

MQTT_Client mqttClient;
static char clientid[66];

void ICACHE_FLASH_ATTR
wifiConnectCb(uint8_t status) {

  // Use the hex encoded system_get_chip_id() value as
  // an unique topic (that still fits on the screen)
  os_sprintf(clientid, "/%0x", system_get_chip_id());

  if (status == STATION_GOT_IP) {
    MQTT_Connect(&mqttClient);
  }
}

void ICACHE_FLASH_ATTR
mqttConnectedCb(uint32_t *args) {
  MQTT_Client* client = (MQTT_Client*) args;
  INFO("MQTT: Connected! will use %s as MQTT topic \n", clientid);
  char *buf = "                            ";
  int i = 0;

  for (i=0; i<6; i++){
    os_sprintf(buf, "/lcd%1d", i);
    MQTT_Subscribe(client, buf, 0);
    os_sprintf(buf, "%s/lcd%1d", clientid, i);
    MQTT_Subscribe(client, buf, 0);
  }

  MQTT_Subscribe(client, "/lcd/clearscreen", 0);
  os_sprintf(buf, "%s/clearscreen", clientid);
  MQTT_Subscribe(client, buf, 0);
  MQTT_Subscribe(client, "/lcd/contrast", 0);
  os_sprintf(buf, "%s/contrast", clientid);
  MQTT_Subscribe(client, buf, 0);
}

void ICACHE_FLASH_ATTR
mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len) {

  char *topicBuf = (char*) os_zalloc(topic_len + 1), *dataBuf = (char*) os_zalloc(data_len + 1);

  MQTT_Client* client = (MQTT_Client*) args;
  os_memcpy(topicBuf, topic, topic_len);
  topicBuf[topic_len] = 0;
  char *sp = topicBuf; // string pointer accessing internals of topicBuf

  os_memcpy(dataBuf, data, data_len);
  dataBuf[data_len] = 0;

  INFO("Received topic: %s, data: %s [%d]\n", topicBuf, dataBuf, data_len);
  if (strncmp(sp, clientid, strlen(clientid)) == 0) {
    sp += strlen(clientid);
  }

  if (strcmp(sp, "/lcd0") == 0) {
    PCD8544_gotoXY(0,0);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if (strcmp(sp, "/lcd1") == 0) {
    PCD8544_gotoXY(0,1);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if (strcmp(sp, "/lcd2") == 0) {
    PCD8544_gotoXY(0,2);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if (strcmp(sp, "/lcd3") == 0) {
    PCD8544_gotoXY(0,3);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if (strcmp(sp, "/lcd4") == 0) {
    PCD8544_gotoXY(0,4);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if (strcmp(sp, "/lcd5") == 0) {
    PCD8544_gotoXY(0,5);
    PCD8544_lcdPrint(dataBuf);
    PCD8544_lcdPad(PCD8544_LCD_CHARS_PER_LINE-data_len);
  } else if ( (strcmp(topicBuf, "/lcd/contrast") == 0) || (strcmp(sp, "/contrast") == 0)) {
    uint8_t contrast = atoi(dataBuf);
    if (contrast>0){
      // atoi("random non-numeric string") will return 0
      INFO("Setting contrast to %d\n", contrast);
      PCD8544_setContrast(contrast);
    }
  } else if ((strcmp(topicBuf, "/lcd/clearscreen") == 0) || (strcmp(sp, "/clearscreen") == 0)) {
    PCD8544_lcdClear();
  }

  os_free(topicBuf);
  os_free(dataBuf);
}

/**
 * Show open hardware logo at startup
 */
static void ICACHE_FLASH_ATTR
lcdInitTask(os_event_t *events) {
  static uint32_t loopIterations = 0;
  loopIterations+=1;
  if (loopIterations < 2) {
    // I wonder why the calls to initLCD in user_init doesn't 'take'
    PCD8544_initLCD(&pcd8544_settings);
    os_delay_us(50000);
    PCD8544_lcdImage(openhardware_logo);
    os_printf("Initiating display: %d\n", loopIterations);
    os_timer_disarm(&lcd_timer);
    os_timer_arm(&lcd_timer, user_procTaskPeriod, 0);
  } else if (loopIterations == 2){
    PCD8544_lcdClear();
    PCD8544_gotoXY(0,0);
    PCD8544_lcdPrint("mqtt topic:");
    PCD8544_gotoXY(0,1);
    PCD8544_lcdPrint(clientid);
  }
}

void ICACHE_FLASH_ATTR
user_init(void) {
  pcd8544_settings.lcdVop = PCD8544_CONTRAST;
  pcd8544_settings.tempCoeff = 0x04;
  pcd8544_settings.biasMode = 0x14;
  pcd8544_settings.inverse = false;

  // you can change these values to any pin you like and have access to
  pcd8544_settings.resetPin = PCD8544_RESET_PIN; //-1; This pin is now optional.
                                                 //   Set it to negative value to disable.
                                                 //   If you do disable it, you must tie LCD reset pin to esp reset via resistor.
  pcd8544_settings.scePin   = PCD8544_SCE_PIN;   //-1; This pin is now optional.
                                                 //   Set it to negative value to disable.
                                                 //   If you do disable it, you must tie LCD CE pin to GND via resistor.
                                                 //   dcPin, sdinPin and sclkPin can be used for other SPI devices if scePin is *NOT* disabled.
  pcd8544_settings.dcPin    = PCD8544_DC_PIN;
  pcd8544_settings.sdinPin  = PCD8544_SDIN_PIN;
  pcd8544_settings.sclkPin  = PCD8544_SCLK_PIN;

  // Make uart0 work with just the TX pin. Baud:115200,n,8,1
  // The RX pin is now free for GPIO use.
  stdout_init();

  os_delay_us(1000000); // wait a second
  PCD8544_init(&pcd8544_settings);
  PCD8544_initLCD(&pcd8544_settings);

  CFG_Load();

  MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);

  MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);

  MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
  MQTT_OnConnected(&mqttClient, mqttConnectedCb);
  MQTT_OnData(&mqttClient, mqttDataCb);

  WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

  os_timer_setfn(&lcd_timer, (os_timer_func_t*) lcdInitTask, NULL);
  os_timer_arm(&lcd_timer, user_procTaskPeriod, 0);

  INFO("\nSystem started ...\n");
}
