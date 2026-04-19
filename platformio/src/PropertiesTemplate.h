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
const char *gatewayMac = "AA:AA:AA:AA:AA:AA";
const char *peerMac = "AA:AA:AA:AA:AA:AA";
const char *pmk = "66536886DB697F700F780F3920F690A9";
const char *lmk = "66536886DB697F700F780F3920F690A0";
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
const char *device_id = "device_id";
const char *device_name = "device_name";