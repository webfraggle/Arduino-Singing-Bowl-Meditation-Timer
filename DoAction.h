/*
Display Time for MicroView
*/
#ifndef DoAction_h
#define DoAction_h

#include "Arduino.h"

class DoAction
{
  public:
    DoAction();
    void out();
    void in();
    void strike();
    void init();
    void refresh();
  private:
    

};

extern DoAction doAction;

#endif
