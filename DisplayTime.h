#ifndef DisplayTime_h
#define DisplayTime_h

#include "Arduino.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayTime
{
  public:
    DisplayTime();
    void show(uint16_t time, Adafruit_SSD1306 *_display);
    void showTimeInMenu(uint16_t time, Adafruit_SSD1306 *_display, uint16_t color);
  private:
    byte getMinute(uint16_t time);
    byte getSecond(uint16_t time);
};

extern DisplayTime displayTime;

#endif
