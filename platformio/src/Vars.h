#pragma once

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <Preferences.h>
#include <EspNowMqttGateway.h>
#include "Properties.h"

EspNowMqttGateway::Peer peer;
Adafruit_NeoPixel pixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Preferences preferences;
Adafruit_USBD_HID usb_hid;
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_CONSUMER()};
int lastCLK;
char currentColor[8] = "#ffffff";
int currentBrightness = 128;