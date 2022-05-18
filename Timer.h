/*
  Timer.h - SubClass for TeaAutomat
*/
#ifndef Timer_h
#define Timer_h

#include <stdint.h>
#include "Arduino.h"
#include <ClickEncoder.h>
#include "DisplayTime.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class Timer
{
  public:
    Timer(Adafruit_SSD1306 *display);
    void start(int16_t rotaryValue,uint16_t zeit);
    void refresh(int16_t rotaryValue, ClickEncoder::Button b);
    byte nextState();
  private:
    int16_t _last;
    byte _nextState;
    uint16_t _time;
    unsigned long _startMillis;
    float percent;
    uint16_t _currentTime;
    bool _finished;
    Adafruit_SSD1306 *_display;
    void display();
    void displayFinished();
  
};

#endif
