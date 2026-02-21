#pragma once
#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/output/float_output.h"
#include <SPI.h>

namespace esphome {
namespace custom_digipot {

static const char *const TAG = "custom_digipot";

class CustomDigipotOutput : public Component, public output::FloatOutput {
 public:
  void set_cs_pin(int pin) { cs_pin_ = pin; }

  void setup() override {
    pinMode(cs_pin_, OUTPUT);
    digitalWrite(cs_pin_, HIGH);
  }

  void digitalPotWrite(byte value) {
    SPI.begin();
    delay(50);
    digitalWrite(cs_pin_, LOW);
    delay(50);
    SPI.transfer(B00010001);
    SPI.transfer(value);
    delay(50);
    digitalWrite(cs_pin_, HIGH);
  }

  void write_state(float state) override {
    byte value = (byte)(state * 255);
    ESP_LOGD(TAG, "write_state %d", (int) value);
    digitalPotWrite(value);
  }

 protected:
  int cs_pin_{16};
};

}  // namespace custom_digipot
}  // namespace esphome
