#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <EspNowMqttGateway.h>
#include <IotCommander.h>
#include "Properties.h"
#include "Led.h"
#include "Hid.h"
#include "Device.h"

void onSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
  Serial.print("ESP-NOW: Send status -> ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

static char output[IOTC_JSON_BUFFER_SIZE];
static char input[IOTC_JSON_BUFFER_SIZE];
void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len)
{
  if (!data || len != sizeof(EspNowMqttGateway::EspNowMessage))
  {
    Serial.println("ESP-NOW: Invalid frame size");
    return;
  }

  const EspNowMqttGateway::EspNowMessage *msg = reinterpret_cast<const EspNowMqttGateway::EspNowMessage *>(data);

  switch (msg->type)
  {
  case EspNowMqttGateway::MessageType::TEXT_MESSAGE:
  {
    char safeTopic[ESP_NOW_MQTT_GATEWAY_TOPIC_SIZE];
    memcpy(safeTopic, msg->payload.mqttEspNowMessage.topic, ESP_NOW_MQTT_GATEWAY_TOPIC_SIZE - 1);
    safeTopic[ESP_NOW_MQTT_GATEWAY_TOPIC_SIZE - 1] = '\0';

    memcpy(input, msg->payload.mqttEspNowMessage.text, IOTC_JSON_BUFFER_SIZE);
    input[IOTC_JSON_BUFFER_SIZE] = '\0';

    Serial.println("------------------------------------------");
    Serial.printf("Data Length: %d\n", len);
    Serial.printf("Topic: %s\n", safeTopic);
    Serial.printf("Text: %s\n", msg->payload.mqttEspNowMessage.text);
    Serial.println("------------------------------------------\n");

    if (strcmp(mqtt_discovery_request_topic, safeTopic) == 0)
    {
      Serial.println("Discovery called");
      device.discovery(output, IOTC_JSON_BUFFER_SIZE);
      peer.mqttMessage(mqtt_discovery_response_topic, output);
    }
    else if (strcmp(mqtt_request_topic, safeTopic) == 0)
    {
      Serial.println("Request called");
      device.request(input, output, IOTC_JSON_BUFFER_SIZE);
      Serial.println("Request result: ");
      Serial.println(output);
      peer.mqttMessage(mqtt_response_topic, output);
    }

    break;
  }

  default:
    Serial.printf("ESP-NOW: Unknown type %d\n", msg->type);
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
  };
  peer.init(peerConfig);

  esp_now_register_recv_cb(onReceive);
  esp_now_register_send_cb(onSent);

  Serial.println("Ready.");
}

void loop()
{
  handleTouch();
  handleEncoder();
}