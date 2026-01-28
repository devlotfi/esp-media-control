#include "Adafruit_TinyUSB.h"

// ---------------- USB HID SETUP ----------------

// HID Consumer Control (media keys)
Adafruit_USBD_HID usb_hid;

// Consumer control report descriptor
uint8_t const hid_report_desc[] = {
  TUD_HID_REPORT_DESC_CONSUMER()
};

// ---------------- PIN CONFIG ----------------

#define POT_PIN     1     // ADC pin (potentiometer)

#define BTN_PREV    10
#define BTN_PLAY    11
#define BTN_NEXT    12

// ---------------- FILTER CONFIG ----------------

#define FILTER_SAMPLES 20    // Moving average window
#define DEAD_BAND       2    // Volume tolerance

// ---------------- GLOBAL VARIABLES ----------------

int adcBuffer[FILTER_SAMPLES];
int adcIndex = 0;
long adcSum = 0;

int stableVolume = 50;   // Virtual volume position (0–100)

// ---------------- MEDIA SEND FUNCTION ----------------

void sendMediaKey(uint16_t key) {
  usb_hid.sendReport16(0, key);
  delay(4);
  usb_hid.sendReport16(0, 0);
}

// ---------------- SETUP ----------------

void setup() {

  // Buttons
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_PLAY, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);

  // ADC config (important for stability)
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  // Initialize ADC filter buffer
  for (int i = 0; i < FILTER_SAMPLES; i++) {
    adcBuffer[i] = analogRead(POT_PIN);
    adcSum += adcBuffer[i];
  }

  // USB HID init
  usb_hid.setReportDescriptor(hid_report_desc, sizeof(hid_report_desc));
  usb_hid.begin();

  // Wait until USB connected
  while (!TinyUSBDevice.mounted()) {
    delay(10);
  }
}

// ---------------- LOOP ----------------

void loop() {

  // -------- POTENTIOMETER FILTER --------

  int rawADC = analogRead(POT_PIN);

  // Moving average filter
  adcSum -= adcBuffer[adcIndex];
  adcBuffer[adcIndex] = rawADC;
  adcSum += rawADC;
  adcIndex = (adcIndex + 1) % FILTER_SAMPLES;

  int filteredADC = adcSum / FILTER_SAMPLES;

  // Map to volume (0–100)
  int targetVolume = map(filteredADC, 0, 4095, 0, 100);

  // Hysteresis control
  if (abs(targetVolume - stableVolume) >= DEAD_BAND) {

    if (targetVolume > stableVolume) {
      sendMediaKey(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
      stableVolume++;
    }

    if (targetVolume < stableVolume) {
      sendMediaKey(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
      stableVolume--;
    }
  }

  // -------- BUTTONS --------

  if (!digitalRead(BTN_PREV)) {
    sendMediaKey(HID_USAGE_CONSUMER_SCAN_PREVIOUS_TRACK);
    delay(250);
  }

  if (!digitalRead(BTN_PLAY)) {
    sendMediaKey(HID_USAGE_CONSUMER_PLAY_PAUSE);
    delay(250);
  }

  if (!digitalRead(BTN_NEXT)) {
    sendMediaKey(HID_USAGE_CONSUMER_SCAN_NEXT_TRACK);
    delay(250);
  }

  // USB rate limit
  delay(8);
}
