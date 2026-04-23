#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <EspNowMqttGateway.h>
#include <EspCommander.h>
#include "Properties.h"
#include "Led.h"
#include "Hid.h"
#include "Device.h"

static char output[ESP_NOW_MQTT_GATEWAY_MQTT_MESSAGE_TEXT_PAYLOAD_SIZE];
void onReceive(const char *topic, const char *text)
{
  if (strcmp(mqtt_discovery_request_topic, topic) == 0)
  {
    Serial.println("Discovery called");
    device.discovery(output, ESP_COMMANDER_JSON_BUFFER_SIZE);
    EspNowMqttGateway::Peer::mqttMessage(mqtt_discovery_response_topic, output);
  }
  else if (strcmp(mqtt_request_topic, topic) == 0)
  {
    Serial.println("Request called");
    device.request(text, output, ESP_COMMANDER_JSON_BUFFER_SIZE);
    Serial.println("Request result: ");
    Serial.println(output);
    EspNowMqttGateway::Peer::mqttMessage(mqtt_response_topic, output);
  }
}

void setup()
{
  Serial.begin(115200);

  setup_hid();
  setup_led();

  EspNowMqttGateway::PeerConfig peerConfig{
      .pmk = pmk,
      .lmk = lmk,
      .gatewayMac = gatewayMac,
      .peerMac = peerMac,
      .channel = channel,
      .handleRecieve = onReceive,
  };
  EspNowMqttGateway::Peer::init(peerConfig);

  Serial.println("Ready.");
}

void loop()
{
  handleTouch();
  handleEncoder();
}