#include "power.hpp"
#include "SolderingCommon.h"
#include "ui_drawing.hpp"
#ifdef OLED_128x32

static void printWatts(void) {
  uint32_t x10Watt = x10WattHistory.average();
  if (x10Watt > 999) {
    OLED::print(SmallSymbolSpace, FontStyle::SMALL);
    OLED::printNumber(x10WattHistory.average() / 10, 3, FontStyle::SMALL);
  } else {
    OLED::printNumber(x10WattHistory.average() / 10, 2, FontStyle::SMALL);
    OLED::print(SmallSymbolDot, FontStyle::SMALL);
    OLED::printNumber(x10WattHistory.average() % 10, 1, FontStyle::SMALL);
  }
  OLED::print(SmallSymbolWatts, FontStyle::SMALL);
}

void ui_draw_soldering_basic_status(bool boostModeOn) {
  uint8_t midX, voltX;
  if (OLED::getRotation()) {
    midX = 12; voltX = 0;
  } else {
    midX = 74; voltX = 116;
  }

  OLED::setCursor(0, 8);
  OLED::printNumber(getTipTemp(), 3, FontStyle::LARGE);
  OLED::printSymbolDeg(FontStyle::EXTRAS);

  OLED::setCursor(midX, 0);
  OLED::printNumber(getSettingValue(SettingsOptions::SolderingTemp), 3, FontStyle::SMALL);
  OLED::printSymbolDeg(FontStyle::SMALL);
  // OLED::print(SmallSymbolSpace, FontStyle::SMALL);
  if (boostModeOn) OLED::drawSymbol(2);

  OLED::setCursor(midX, 8);
  printWatts();

  OLED::setCursor(midX, 16);
  OLED::drawSymbol(14);
  uint8_t heat = X10WattsToPWM(x10WattHistory.average()) / 31;
  OLED::drawFilledRect(midX, 16, midX + 12, 16 + 2 + (8 - heat), true);

  OLED::setCursor(voltX, 0);
  ui_draw_power_source_icon();
}

#endif
