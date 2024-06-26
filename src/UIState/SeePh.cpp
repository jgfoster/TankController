/**
 * SeePIDConstants.cpp
 */

#include "SeePh.h"

#include "model/PHControl.h"
#include "model/PHProbe.h"
#include "model/TC_util.h"
#include "wrappers/DateTime_TC.h"
#include "wrappers/LiquidCrystal_TC.h"

void SeePh::loop() {
  int32_t oddEven = ((millis() - startTime) / 3000) % 2;
  switch (oddEven) {
    case 0:
      loadHeader(0);
      loadValues(1);
      break;
    case 1:
      loadPHFunctionType(0);
      loadTypeVariables(1);
      break;
  }
}

void SeePh::loadPHFunctionType(uint16_t line) {
  char buffer[17];
  char *type;
  switch (PHControl::instance()->getPHFunctionType()) {
    case PHControl::FLAT_TYPE: {
      type = (char *)"flat";
      break;
    }
    case PHControl::RAMP_TYPE: {
      type = (char *)"ramp";
      break;
    }
    case PHControl::SINE_TYPE: {
      type = (char *)"sine";
      break;
    }
    default: {
      type = (char *)"????";
      break;
    }
  }
  snprintf_P(buffer, sizeof(buffer), (PGM_P)F("type: %s"), type);
  LiquidCrystal_TC::instance()->writeLine(buffer, line);
}

void SeePh::loadTypeVariables(uint16_t line) {
  char buffer[17];
  switch (PHControl::instance()->getPHFunctionType()) {
    case PHControl::FLAT_TYPE: {
      break;
    }
    case PHControl::RAMP_TYPE: {
      uint32_t endTime = PHControl::instance()->getPhRampTimeEnd();
      uint32_t currentTime = DateTime_TC::now().secondstime();
      int timeLeft = endTime - currentTime;
      timeLeft = timeLeft > 0 ? timeLeft : 0;
      int timeLeftMinutes = timeLeft / 60;
      int timeLeftHours = timeLeft / 3600;
      int timeLeftSeconds = timeLeft % 60;
      snprintf_P(buffer, sizeof(buffer), (PGM_P)F("left: %i:%i:%i"), timeLeftHours, timeLeftMinutes, timeLeftSeconds);
      LiquidCrystal_TC::instance()->writeLine(buffer, line);
      break;
    }
    case PHControl::SINE_TYPE: {
      uint32_t periodInSeconds = PHControl::instance()->getPeriodInSeconds();
      float periodHours = periodInSeconds / 3600.0;
      float amplitude = PHControl::instance()->getAmplitude();

      snprintf_P(buffer, sizeof(buffer), (PGM_P)F("p=%i.%03i a=%i.%03i"), (int)periodHours,
                 (int)(periodHours * 1000) % 1000, (int)amplitude, (int)(amplitude * 1000) % 1000);
      LiquidCrystal_TC::instance()->writeLine(buffer, line);
      break;
    }
    default:
      break;
  }
}

void SeePh::loadHeader(uint16_t line) {
  char buffer[17];
  snprintf_P(buffer, sizeof(buffer), (PGM_P)F("Now  Next  Goal"));
  LiquidCrystal_TC::instance()->writeLine(buffer, line);
}

void SeePh::loadValues(uint16_t line) {
  char buffer[17];
  float overallTargetPh = PHControl::instance()->getBaseTargetPh();
  float currentTargetPh = PHControl::instance()->getCurrentTargetPh();
  float currentPh = PHProbe::instance()->getPh();
  snprintf_P(buffer, sizeof(buffer), (PGM_P)F("%i.%02i %i.%03i %i.%03i"), (int)currentPh,
             (int)(currentPh * 100 + 0.5) % 100, (int)currentTargetPh, (int)(currentTargetPh * 1000 + 0.5) % 1000,
             (int)overallTargetPh, (int)(overallTargetPh * 1000) % 1000);
  LiquidCrystal_TC::instance()->writeLine(buffer, line);
}
