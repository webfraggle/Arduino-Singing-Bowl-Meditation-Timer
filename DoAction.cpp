#include "Arduino.h"
#include "DoAction.h"

#define STRIKE_PIN     8

DoAction::DoAction(){
}
void DoAction::strike() {
  digitalWrite(STRIKE_PIN, HIGH);
  delay(500);
  digitalWrite(STRIKE_PIN, LOW);
}
void DoAction::out() {
}
void DoAction::in() {
}
void DoAction::init() {
  pinMode(STRIKE_PIN, OUTPUT);
}


DoAction doAction;
