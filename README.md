<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/github-banner.png">

# 📜 arduino-altimeter

The goal of this project is to create a smart media control panel using the OSB OTG capabilities of ESP32S3

# 📌 Contents

- [Tech stack](#tech-stack)
- [Building the altitude sensor](#building-the-altitude-sensor)
  - [Components](#components)
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

# Building the Altitude Sensor

## Components

- ESP32S3
- Potentiometer (10kΩ)
- 3 Button
- Cables
- Case (Optional)

<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/fritzing.png">

## Configuration

To avoid any issues you mus use Arduino IDE to upload the code with this config:

- USB CDC on boot "Enabled"
- USB Mode "USB-OTG (TinyUSB)"

## Images

Some images of the final build

<img src="https://raw.githubusercontent.com/devlotfi/esp-media-control/master/github-assets/build.jpg">

