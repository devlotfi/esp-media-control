#pragma once

#include <Arduino.h>

// ----------------------
// Preferences namespace
// ----------------------
#define PREFERENCES_NAMESAPCE "DEVICE"

// ----------------------
// Pin connections
// ----------------------
#define LED_PIN 48
#define LED_COUNT 1
// Touch pins
#define TOUCH_PREV 10
#define TOUCH_PLAY 11
#define TOUCH_NEXT 12
// Encoder pins
#define ENC_SW 16
#define ENC_DT 17
#define ENC_CLK 18

// ----------------------
// ESP-NOW MQTT Gateway config
// ----------------------
const char *gatewayMac = "30:AE:A4:11:22:33";
const char *peerMac = "56:E3:7D:FC:8A:57";
const char *pmk = "1187BA60CAA9A7FA52B2B8C4141B4A9D";
const char *lmk = "14C5FEBD4AFB3097011BD40CD8A5BAF2";
uint8_t channel = 1;

// ----------------------
// MQTT Topics
// ----------------------
const char *mqtt_discovery_request_topic = "esp-commander/discovery/request";
const char *mqtt_discovery_response_topic = "esp-commander/discovery/response";
const char *mqtt_request_topic = "esp-commander/esp-media-control/request";
const char *mqtt_response_topic = "esp-commander/esp-media-control/response";

// ----------------------
// Device
// ----------------------
const char *device_id = "5d0c4638-24d5-4f05-b318-3f8597ad26ac";
const char *device_name = "MEDIA_CONTROL";