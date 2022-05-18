#include "Arduino.h"
#include "DisplayTime.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeSans18pt7b.h>

DisplayTime::DisplayTime()
{
}


void DisplayTime::show(uint16_t time, Adafruit_SSD1306 *_display)
{
  //Serial.println(time);
  //_display->setFont(&FreeSans18pt7b);
  _display->setTextSize(2);
  _display->setCursor(20,40);
  byte min = getMinute(time);
  if (min < 10)
  {
    _display->print(String("  ")+String(min));
  } else {
    _display->print(min);
  }
  
  _display->setCursor(70,40);
  byte sec = getSecond(time);
  if (sec < 10)
  {
    _display->print(String(0)+String(sec));
    
  } else {
    _display->print(sec);
  
  }
  
  _display->setCursor(64,40);
  _display->print(":");
}

void DisplayTime::showTimeInMenu(uint16_t time, Adafruit_SSD1306 *_display, uint16_t color)
{
  _display->setTextColor(color);
  _display->setCursor(73,28);
  byte min = getMinute(time);
  if (min < 10)
  {
    _display->print(String("  ")+String(min));
  } else {
    _display->print(min);
  }
  
  _display->setCursor(100,28);
  byte sec = getSecond(time);
  if (sec < 10)
  {
    _display->print(String(0)+String(sec));
    
  } else {
    _display->print(sec);
  
  }
  _display->setCursor(95,28);
  _display->print(":");
}

byte DisplayTime::getMinute(uint16_t time)
{
  return time/60;
}

byte DisplayTime::getSecond(uint16_t time)
{
  return time%60;
}

DisplayTime displayTime;
