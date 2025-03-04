#pragma once
#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__ 1
#endif
#include <Arduino.h>

#include "model/TC_util.h"
#define TURN_SOLENOID_OFF HIGH
#define TURN_SOLENOID_ON LOW
class LiquidCrystal_TC;
class Serial_TC;
class UIState;
class TankController {
public:
  // class methods
  static TankController* instance(const char* remoteLogName = nullptr, const char* pushingBoxID = nullptr,
                                  int tzOffsetHrs = -7);
  static void deleteInstance();

  // instance methods
  bool isInCalibration();
  int freeMemory();
  void loop(bool report_loop_delay = false);
  void serialEvent();
  void serialEvent1();
  void setNextState(UIState* newState, bool update = false);
  void setup();
  const __FlashStringHelper* stateName();
  const char* version();
  void setNextKey(char value) {
    nextKey = value;
  }

#if defined(ARDUINO_CI_COMPILATION_MOCKS)
  int loopDelayCount = 0;
#endif

private:
  // class variables
  static TankController* _instance;
  static const uint32_t IDLE_TIMEOUT = 60L * 1000L;  // revert to the main menu after 60 seconds of inactivity
  // instance variables
  UIState* state = nullptr;
  UIState* nextState = nullptr;
  uint32_t lastKeypadTime = 0;
  char nextKey = 0;

  // instance methods
  TankController();
  ~TankController();
  void blink();
  void handleUI();
  void updateControls();
  void updateState();
};
