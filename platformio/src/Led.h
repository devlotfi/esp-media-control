#pragma once

#include <stdint.h>
#include "Vars.h"

struct LedConfig
{
  int brightness;
  char color[8];
};

void saveConfig(LedConfig conf)
{
  preferences.putBytes("led", &conf, sizeof(LedConfig));
}

LedConfig loadConfig()
{
  LedConfig conf = {
      .brightness = 128,
      .color = "#ffffff"};
  preferences.getBytes("led", &conf, sizeof(LedConfig));
  return conf;
}

void setLed(const char *hexColor, const uint8_t brightness)
{
  if (hexColor[0] == '#')
  {
    hexColor++;
  }

  // Convert hex string to 24-bit number
  uint32_t color = strtol(hexColor, NULL, 16);

  // Extract RGB components
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = color & 0xFF;

  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.setBrightness(brightness);
  pixel.show();
}

void setup_led()
{
  preferences.begin(PREFERENCES_NAMESAPCE, false);
  auto ledConfig = loadConfig();
  strncpy(currentColor, ledConfig.color, sizeof(currentColor) - 1);
  currentColor[sizeof(currentColor) - 1] = '\0';
  currentBrightness = ledConfig.brightness;
  Serial.println(ledConfig.color);
  Serial.println(ledConfig.brightness);
  setLed(ledConfig.color, ledConfig.brightness);
}