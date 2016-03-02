#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

#define CFG_HOLDER	0x00FF55A4	/* Change this value to load default configurations */
#define CFG_LOCATION	0x3C	/* Please don't change or if you know what you doing */
#define CLIENT_SSL_ENABLE

/*DEFAULT CONFIGURATIONS*/

#define MQTT_HOST			"192.168.11.122" //or "mqtt.yourdomain.com"
#define MQTT_PORT			1880
#define MQTT_BUF_SIZE		1024
#define MQTT_KEEPALIVE		120	 /*second*/

#define MQTT_CLIENT_ID		"DVES_%08X"
#define MQTT_USER			"DVES_USER"
#define MQTT_PASS			"DVES_PASS"

#define STA_SSID "DVES_HOME"
#define STA_PASS "yourpassword"
#define STA_TYPE AUTH_WPA2_PSK

#define MQTT_RECONNECT_TIMEOUT 	5	/*second*/

#define DEFAULT_SECURITY	0
#define QUEUE_BUFFER_SIZE		 		2048

#define PROTOCOL_NAMEv31	/*MQTT version 3.1 compatible with Mosquitto v0.15*/
//PROTOCOL_NAMEv311			/*MQTT version 3.11 compatible with https://eclipse.org/paho/clients/testing/*/

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
