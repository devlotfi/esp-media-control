#pragma once

#include <stdint.h>
#include "Properties.h"
#include "Vars.h"

// Send consumer control command
void sendConsumer(uint16_t key) {
  usb_hid.sendReport(0, &key, 2);
  delay(10);
  key = 0;  // release
  usb_hid.sendReport(0, &key, 2);
}

void handleTouch() {
  if (digitalRead(TOUCH_PREV)) {
    sendConsumer(HID_USAGE_CONSUMER_SCAN_PREVIOUS_TRACK);
    delay(250);
  }

  if (digitalRead(TOUCH_PLAY)) {
    sendConsumer(HID_USAGE_CONSUMER_PLAY_PAUSE);
    delay(250);
  }

  if (digitalRead(TOUCH_NEXT)) {
    sendConsumer(HID_USAGE_CONSUMER_SCAN_NEXT_TRACK);
    delay(250);
  }
}

void handleEncoder() {
  int currentCLK = digitalRead(ENC_CLK);

  if (currentCLK != lastCLK) {
    if (digitalRead(ENC_DT) != currentCLK) {
      sendConsumer(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
    } else {
      sendConsumer(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
    }
  }

  lastCLK = currentCLK;

  if (digitalRead(ENC_SW) == LOW) {
    sendConsumer(HID_USAGE_CONSUMER_MUTE);
    delay(250);
  }
}