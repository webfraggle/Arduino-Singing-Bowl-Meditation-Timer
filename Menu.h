/*
  Menu.h - Rotary Encoder Menu Class for MicroView
*/
#ifndef Morse_h
#define Morse_h

#include <stdint.h>
#include "Arduino.h"
#include <ClickEncoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Menu
{
  public:
    Menu(Adafruit_SSD1306 *display);
    void start(int16_t rotaryValue, uint16_t zeit);
    void refresh(int16_t rotaryValue, ClickEncoder::Button b);
    byte nextState();
  private:
    int16_t _last;
    byte _menuPosition;
    byte _nextState;
    byte _maxMenuItems;
    long previousMillis;
    uint16_t _time;
    bool t;
    Adafruit_SSD1306 *_display;
    void display();
    void drawBitmap(uint8_t * bitArray);
};

#endif
