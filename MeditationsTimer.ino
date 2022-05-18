#include <Servo.h>

#include "Arduino.h"
#include <MsTimer2.h>
#include <ClickEncoder.h>
#include <EEPROMex.h>
#include "DisplayTime.h"
#include "Menu.h"
#include "SetMyTime.h"
#include "Timer.h"
#include "DoAction.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Menu *menu;
SetMyTime *settime;
Timer *timer;

ClickEncoder *encoder;
int16_t last, value;
byte nextState = 255;
byte lastState=255;
byte currentState=0;

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void timerIsr() {
  encoder->service();
}


void setup() {
  Serial.begin(9600);

  
  encoder = new ClickEncoder(8, 9, 10, 4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.display();
  delay(1000); // Pause for 2 seconds

  MsTimer2::set(1,timerIsr);
  MsTimer2::start();
  //Timer1.initialize(1000);

  //Timer1.attachInterrupt(timerIsr);
  
  last = -1;
  //uView.begin();
  //uView.clear(PAGE);      // clear the page buffer

  //displayTime.show(1099);
  doAction.init();

  
  delay(100);
  display.clearDisplay();
  Serial.println(F("After Clear"));
  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.drawPixel(20, 20, SSD1306_WHITE);
  display.display();

  menu = new Menu(&display);
  timer = new Timer(&display);
  settime = new SetMyTime(&display);
  
  
}

void loop() {

//Serial.print("11");
  value += encoder->getValue();
  if (value != last) {
    
    Serial.print("Encoder Value: ");
    Serial.println(value);
    
    
  }
  ClickEncoder::Button b = encoder->getButton();
  //Serial.println(currentState);
  switch (currentState)
  {
    // Statemachine
    // jeweils refresh mit button & value, dann Abfrage von nextState: -1 nix, oder nummer.
    
    // bei Nummer z.B. Wert abfragen  und speichern und nÃ¤chsten State aufrufen. 
    case 0:
      if (lastState != currentState)
      {
        menu->start(value, settime->time());
        lastState = currentState;
      }
      menu->refresh(value, b);
      nextState = menu->nextState();
      if (nextState != 255)
      {
        Serial.print("nextState ");
        Serial.println(nextState);
        currentState = nextState;
      }
    break;
    case 1:
      if (lastState != currentState)
      {
        timer->start(value, settime->time());
        lastState = currentState;
      }
      timer->refresh(value, b);
      nextState = timer->nextState();
      if (nextState != 255)
      {
        //Serial.print("nextState ");
        //Serial.println(nextState);
        currentState = nextState;
      }
      
      
    break;
    case 2:
      if (lastState != currentState)
      {
        //Serial.println(value);
        settime->start(value);
        lastState = currentState;
      }
      settime->refresh(value, b);
      nextState = settime->nextState();
      if (nextState != 255)
      {
        currentState = nextState;
      }
    break;
    
  }
  last = value;

}
