/*
  SetMyTime.h - SubClass for MeditationTimer
*/
#ifndef SetMyTime_h
#define SetMyTime_h

#include <stdint.h>
#include "Arduino.h"
#include <ClickEncoder.h>
#include "DisplayTime.h"
#include <EEPROMex.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



class SetMyTime
{
  public:
    SetMyTime(Adafruit_SSD1306 *display);
    void start(int16_t rotaryValue);
    void refresh(int16_t rotaryValue, ClickEncoder::Button b);
    uint16_t time();
    byte nextState();
  private:
    int16_t _test;
    int16_t _last;
    byte _nextState;
    uint16_t _time;
    Adafruit_SSD1306 *_display;
    
    
    void display();
    void save();
  
};

#endif
