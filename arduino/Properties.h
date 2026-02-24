#pragma once

// ----------------------
// Preferences namespace
// ----------------------
#define PREFERENCES_NAMESAPCE "LED"

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
// Wi-Fi credentials
// ----------------------
const char *ssid = "ssid";
const char *password = "password";

// ----------------------
// MQTT credentials
// ----------------------
const char *mqtt_server = "mqtt_server";
const int mqtt_port = 8883;
const char *mqtt_user = "mqtt_user";
const char *mqtt_password = "mqtt_password";

// ----------------------
// MQTT Topics
// ----------------------
const char *mqtt_discovery_request_topic = "iot-commander/discovery/request";
const char *mqtt_discovery_response_topic = "iot-commander/discovery/response";
const char *mqtt_request_topic = "iot-commander/UUID/request";
const char *mqtt_response_topic = "iot-commander/UUID/response";

// ----------------------
// Device
// ----------------------
const char *device_id = "device_id";
const char *device_name = "device_name";

// ----------------------
// TLS Root Certificate
// ----------------------
const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
...
-----END CERTIFICATE-----
)EOF";