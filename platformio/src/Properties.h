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
uint8_t gatewayMacByte[6] = {0x30, 0xAE, 0xA4, 0x11, 0x22, 0x33};
uint8_t deviceMacByte[6] = {0x30, 0xAE, 0xA4, 0x11, 0x22, 0x23};
const char *gatewayMac = "30:AE:A4:11:22:33";
const char *peerMac = "30:AE:A4:11:22:23";
const char *pmk = "66536886DB697F700F780F3920F690A9";
const char *lmk = "66536886DB697F700F780F3920F690A0";
uint8_t channel = 1;

// ----------------------
// MQTT Topics
// ----------------------
const char *mqtt_discovery_request_topic = "iot-commander/discovery/request";
const char *mqtt_discovery_response_topic = "iot-commander/discovery/response";
const char *mqtt_request_topic = "iot-commander/esp-media-control/request";
const char *mqtt_response_topic = "iot-commander/esp-media-control/response";

// ----------------------
// Device
// ----------------------
const char *device_id = "5d0c4638-24d5-4f05-b318-3f8597ad26ac";
const char *device_name = "MEDIA_CONTROL";