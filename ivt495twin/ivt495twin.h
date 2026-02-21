#pragma once
#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace ivt495twin {

static const char *const TAG = "ivt495twin";

class Ivt495Twin : public PollingComponent, public uart::UARTDevice {
 public:
  Ivt495Twin() = default;

  // Setters for each sensor (called from Python-generated code)
  void set_sensor1(sensor::Sensor *s)  { xsensor1  = s; }
  void set_sensor2(sensor::Sensor *s)  { xsensor2  = s; }
  void set_sensor3(sensor::Sensor *s)  { xsensor3  = s; }
  void set_sensor4(sensor::Sensor *s)  { xsensor4  = s; }
  void set_sensor5(sensor::Sensor *s)  { xsensor5  = s; }
  void set_sensor6(sensor::Sensor *s)  { xsensor6  = s; }
  void set_sensor7(sensor::Sensor *s)  { xsensor7  = s; }
  void set_sensor8(sensor::Sensor *s)  { xsensor8  = s; }
  void set_sensor9(sensor::Sensor *s)  { xsensor9  = s; }
  void set_sensor10(sensor::Sensor *s) { xsensor10 = s; }
  void set_sensor11(sensor::Sensor *s) { xsensor11 = s; }
  void set_sensor12(sensor::Sensor *s) { xsensor12 = s; }
  void set_sensor13(sensor::Sensor *s) { xsensor13 = s; }
  void set_sensor14(sensor::Sensor *s) { xsensor14 = s; }
  void set_sensor15(sensor::Sensor *s) { xsensor15 = s; }
  void set_sensor16(sensor::Sensor *s) { xsensor16 = s; }
  void set_sensor17(sensor::Sensor *s) { xsensor17 = s; }
  void set_sensor18(sensor::Sensor *s) { xsensor18 = s; }
  void set_sensor19(sensor::Sensor *s) { xsensor19 = s; }
  void set_sensor20(sensor::Sensor *s) { xsensor20 = s; }
  void set_sensor21(sensor::Sensor *s) { xsensor21 = s; }
  void set_sensor22(sensor::Sensor *s) { xsensor22 = s; }
  void set_sensor23(sensor::Sensor *s) { xsensor23 = s; }
  void set_sensor24(sensor::Sensor *s) { xsensor24 = s; }
  void set_sensor25(sensor::Sensor *s) { xsensor25 = s; }
  void set_sensor26(sensor::Sensor *s) { xsensor26 = s; }
  void set_sensor27(sensor::Sensor *s) { xsensor27 = s; }
  void set_sensor28(sensor::Sensor *s) { xsensor28 = s; }
  void set_sensor29(sensor::Sensor *s) { xsensor29 = s; }
  void set_sensor30(sensor::Sensor *s) { xsensor30 = s; }
  void set_sensor31(sensor::Sensor *s) { xsensor31 = s; }
  void set_sensor32(sensor::Sensor *s) { xsensor32 = s; }
  void set_sensor33(sensor::Sensor *s) { xsensor33 = s; }
  void set_sensor34(sensor::Sensor *s) { xsensor34 = s; }
  void set_sensor35(sensor::Sensor *s) { xsensor35 = s; }
  void set_sensor36(sensor::Sensor *s) { xsensor36 = s; }

  void setup() override {
    this->set_update_interval(60000);
  }

  void update() override {}

  void loop() override {
    if (available() > 1) {
      ESP_LOGD(TAG, "Loop() - data available");
      delay(100);
      fetchSerial();
      splitString();
      publishState();
    }
    delay(100);
  }

 protected:
  sensor::Sensor *xsensor1  {nullptr};
  sensor::Sensor *xsensor2  {nullptr};
  sensor::Sensor *xsensor3  {nullptr};
  sensor::Sensor *xsensor4  {nullptr};
  sensor::Sensor *xsensor5  {nullptr};
  sensor::Sensor *xsensor6  {nullptr};
  sensor::Sensor *xsensor7  {nullptr};
  sensor::Sensor *xsensor8  {nullptr};
  sensor::Sensor *xsensor9  {nullptr};
  sensor::Sensor *xsensor10 {nullptr};
  sensor::Sensor *xsensor11 {nullptr};
  sensor::Sensor *xsensor12 {nullptr};
  sensor::Sensor *xsensor13 {nullptr};
  sensor::Sensor *xsensor14 {nullptr};
  sensor::Sensor *xsensor15 {nullptr};
  sensor::Sensor *xsensor16 {nullptr};
  sensor::Sensor *xsensor17 {nullptr};
  sensor::Sensor *xsensor18 {nullptr};
  sensor::Sensor *xsensor19 {nullptr};
  sensor::Sensor *xsensor20 {nullptr};
  sensor::Sensor *xsensor21 {nullptr};
  sensor::Sensor *xsensor22 {nullptr};
  sensor::Sensor *xsensor23 {nullptr};
  sensor::Sensor *xsensor24 {nullptr};
  sensor::Sensor *xsensor25 {nullptr};
  sensor::Sensor *xsensor26 {nullptr};
  sensor::Sensor *xsensor27 {nullptr};
  sensor::Sensor *xsensor28 {nullptr};
  sensor::Sensor *xsensor29 {nullptr};
  sensor::Sensor *xsensor30 {nullptr};
  sensor::Sensor *xsensor31 {nullptr};
  sensor::Sensor *xsensor32 {nullptr};
  sensor::Sensor *xsensor33 {nullptr};
  sensor::Sensor *xsensor34 {nullptr};
  sensor::Sensor *xsensor35 {nullptr};
  sensor::Sensor *xsensor36 {nullptr};

  String inputString;
  boolean stringComplete = false;
  char inChar;
  int counter = 0;
  int commaPosition = 0;
  float ivt[50] = {0};

  void fetchSerial() {
    while (available() > 0) {
      inChar = read();
      if (inChar != 32) {
        inputString += inChar;
      }
      delay(2);
    }
    inChar = '0';
    //Serial.println(inputString);
    ESP_LOGD(TAG, "RX: %s", inputString.c_str());
    stringComplete = true;
  }

  void splitString() {
    commaPosition = inputString.indexOf(';');
    while (commaPosition >= 0) {
      commaPosition = inputString.indexOf(';');
      if (commaPosition != -1) {
        ivt[counter] = stringToFloat(inputString.substring(0, commaPosition));
        inputString = inputString.substring(commaPosition + 1, inputString.length());
      } else {
        if (inputString.length() > 0) {
          ivt[counter] = stringToFloat(inputString.substring(0, commaPosition));
        }
      }
      while (ivt[counter] > (float) 1200) {
        ivt[counter] = ivt[counter] / (float) 10;
      }
      counter++;
    }
    counter = 0;
    inputString = "";
    commaPosition = 0;
  }

  float stringToFloat(String input) {
    String stringTemp = input;
    char stfarray[stringTemp.length() + 1];
    stringTemp.toCharArray(stfarray, sizeof(stfarray));
    float stf = atof(stfarray);
    stringTemp = "";
    memset(stfarray, 0, sizeof stfarray);
    return stf;
  }

  void publishState() {
    if (xsensor1  != nullptr) xsensor1->publish_state(ivt[1]  / 10.0f);
    if (xsensor2  != nullptr) xsensor2->publish_state(ivt[2]  / 10.0f);
    if (xsensor3  != nullptr) xsensor3->publish_state(ivt[3]  / 10.0f);
    if (xsensor4  != nullptr) xsensor4->publish_state(ivt[4]  / 10.0f);
    if (xsensor5  != nullptr) xsensor5->publish_state(ivt[5]  / 10.0f);
    if (xsensor6  != nullptr) xsensor6->publish_state(ivt[6]  / 10.0f);
    if (xsensor7  != nullptr) xsensor7->publish_state(ivt[7]  / 10.0f);
    if (xsensor8  != nullptr) xsensor8->publish_state(ivt[8]  / 10.0f);
    if (xsensor9  != nullptr) xsensor9->publish_state((bool)(int) ivt[9]);
    if (xsensor10 != nullptr) xsensor10->publish_state((bool)(int) ivt[10]);
    if (xsensor11 != nullptr) xsensor11->publish_state((bool)(int) ivt[11]);
    if (xsensor12 != nullptr) xsensor12->publish_state((bool)(int) ivt[12]);
    if (xsensor13 != nullptr) xsensor13->publish_state((bool)(int) ivt[13]);
    if (xsensor14 != nullptr) xsensor14->publish_state((bool)(int) ivt[14]);
    if (xsensor15 != nullptr) xsensor15->publish_state((bool)(int) ivt[15]);
    if (xsensor16 != nullptr) xsensor16->publish_state((int) ivt[16]);
    if (xsensor17 != nullptr) xsensor17->publish_state((bool)(int) ivt[17]);
    if (xsensor18 != nullptr) xsensor18->publish_state((bool)(int) ivt[18]);
    if (xsensor19 != nullptr) xsensor19->publish_state((int) ivt[19]);
    if (xsensor20 != nullptr) xsensor20->publish_state(ivt[20] / 10.0f);
    if (xsensor21 != nullptr) xsensor21->publish_state(ivt[21] / 10.0f);
    if (xsensor22 != nullptr) xsensor22->publish_state(ivt[22] / 10.0f);
    if (xsensor23 != nullptr) xsensor23->publish_state(ivt[23] / 10.0f);
    if (xsensor24 != nullptr) xsensor24->publish_state(ivt[24] / 10.0f);
    if (xsensor25 != nullptr) xsensor25->publish_state(ivt[25] / 10.0f);
    if (xsensor26 != nullptr) xsensor26->publish_state(ivt[26] / 10.0f);
    if (xsensor27 != nullptr) xsensor27->publish_state(ivt[27] / 10.0f);
    if (xsensor28 != nullptr) xsensor28->publish_state(ivt[28] / 10.0f);
    if (xsensor29 != nullptr) xsensor29->publish_state(ivt[29] / 10.0f);
    if (xsensor30 != nullptr) xsensor30->publish_state(ivt[30] / 10.0f);
    if (xsensor31 != nullptr) xsensor31->publish_state(ivt[31] / 10.0f);
    if (xsensor32 != nullptr) xsensor32->publish_state((bool)(int) ivt[32]);
    if (xsensor33 != nullptr) xsensor33->publish_state((int) ivt[33]);
    if (xsensor34 != nullptr) xsensor34->publish_state((int) ivt[34]);
    if (xsensor35 != nullptr) xsensor35->publish_state(ivt[35] / 10.0f);
    if (xsensor36 != nullptr) xsensor36->publish_state((bool)(int) ivt[36]);
  }
};

}  // namespace ivt495twin
}  // namespace esphome
