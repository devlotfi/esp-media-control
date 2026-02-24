#pragma once

#include "Embedded_Template_Library.h"
#include <etl/variant.h>
#include <stdint.h>
#include <IotCommander.h>
#include "Properties.h"
#include "Vars.h"
#include "Led.h"

IotCommander::Value rgbLedQueryResults[] = {
    IotCommander::Value(IotCommander::Value::Params{
        .name = "color",
        .type = IotCommander::ValueType::COLOR,
        .required = true,
    }),
    IotCommander::Value(IotCommander::Value::Params{
        .name = "brightness",
        .type = IotCommander::ValueType::RANGE,
        .required = true,
        .min = 0,
        .max = 255,
    }),
};
auto rgbLedQuery = IotCommander::Query(IotCommander::Query::Params{
    .name = "RGB Led",
    .results = rgbLedQueryResults,
    .handler = [](IotCommander::HandlerValue results[], etl::optional<const char *> &error)
    {
      results[0] = (const char*) currentColor;
      results[1] = (int) currentBrightness;
    },
});

IotCommander::Value setRgbLedActionParameters[] = {
    IotCommander::Value(IotCommander::Value::Params{
        .name = "color",
        .type = IotCommander::ValueType::COLOR,
        .required = true,
    }),
    IotCommander::Value(IotCommander::Value::Params{
        .name = "brightness",
        .type = IotCommander::ValueType::RANGE,
        .required = true,
        .min = 0,
        .max = 255,
    }),
};
auto setRgbLedAction = IotCommander::Action(IotCommander::Action::Params{
    .name = "set RGB LED",
    .parameters = setRgbLedActionParameters,
    .handler = [](IotCommander::HandlerValue parameters[], IotCommander::HandlerValue results[], etl::optional<const char *> &error)
    {
        const char* colorParam = etl::get<const char*>(parameters[0].value());
        int brightnessParam = etl::get<int>(parameters[1].value());

        strncpy(currentColor, colorParam, sizeof(currentColor) - 1);
        currentColor[sizeof(currentColor) - 1] = '\0';
        currentBrightness = brightnessParam;

        Serial.println(currentColor);
        Serial.println(currentBrightness);

        LedConfig ledConfig = {};
        ledConfig.brightness = currentBrightness;
        strncpy(ledConfig.color, currentColor, sizeof(ledConfig.color) - 1);
        ledConfig.color[sizeof(ledConfig.color) - 1] = '\0';
        saveConfig(ledConfig);
        setLed(colorParam, (uint8_t) currentBrightness);
    },
});

static uint8_t requestBuffer[IOTC_JSON_BUFFER_SIZE];
static uint8_t responseBuffer[IOTC_JSON_BUFFER_SIZE];
IotCommander::StaticBufferAllocator requestAllocator(requestBuffer, sizeof(requestBuffer));
IotCommander::StaticBufferAllocator responseAllocator(responseBuffer, sizeof(responseBuffer));

IotCommander::Query queries[] = {
    rgbLedQuery,
};
IotCommander::Action actions[] = {
    setRgbLedAction
};
auto device = IotCommander::Device(IotCommander::Device::Params{
    .id = device_id,
    .name = device_name,
    .requestTopic = mqtt_request_topic,
    .responseTopic = mqtt_response_topic,
    .queries = queries,
    .actions = actions,
    .requestAllocator = requestAllocator,
    .responseAllocator = responseAllocator,
});