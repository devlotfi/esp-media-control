<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/github-banner.png">

# 📜 esp-media-control

The goal of this project is to create a smart media control panel using the OSB OTG capabilities of ESP32S3

## Features

- Volume UP/DOWN
- Volume Mute
- Previous / Pause / Next

# 📌 Contents

- [Tech stack](#tech-stack)
- [Building the media controller](#building-the-media-controller)
  - [Components](#components)
  - [Libraries](#libraries)
  - [Configuration](#configuration)
  - [Images](#images)

# Tech stack

<p float="left">
  <img height="50px" src="https://devlotfi.github.io/stack-icons/icons/arduino.svg">
  <img height="50px" src="https://devlotfi.github.io/stack-icons/icons/espressif.svg">
</p>

## Diagrams

<p float="left">
  <img height="50px" src="https://devlotfi.github.io/stack-icons/icons/fritzing.svg">
</p>

# Building the Media Controller

## Components

- ESP32S3
- Rotary Encoder Module (EC11)
- 3 Touch Modules (TTP223)
- Cables
- Case (Optional)

<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/fritzing.png">

## Libraries

- ArduinoJson
- Embedded Template Library ETL
- Adafruit NeoPixel
- Adafruit TinyUSB
- PubSubClient
- [IotCommander](https://github.com/devlotfi/iot-commander) 

## Configuration

To avoid any issues you mus use Arduino IDE to upload the code with this config:

- USB CDC on boot "Enabled"
- USB Mode "USB-OTG (TinyUSB)"

Change settings in [Properties.h](https://github.com/devlotfi/esp-media-control/blob/master/arduino/Properties.h)

The baord relied on an MQTT communication to change the RGB LED Color uisng [IotCommander](https://github.com/devlotfi/iot-commander)

## Images

Some images of the final build

<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/build.jpg">
