
#include "Arduino.h"
#include "Timer.h"
#include <ClickEncoder.h>

#include "DisplayTime.h"
#include "DoAction.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Timer::Timer(Adafruit_SSD1306 *display) :
		_last(0), _nextState(255), _time(0), _startMillis(0), percent(0), _currentTime(
				0), _finished(false) {
          _display = display;

	//Serial.println("Timer");
}

void Timer::refresh(int16_t rotaryValue, ClickEncoder::Button b) {

	unsigned long diff = ((millis() - _startMillis));


	if (!_finished) {
		//Serial.println(_time*1000);
		//Serial.println(diff);
		//Serial.println(float(diff)/float(_time*1000));
		unsigned long t = _time;
		t = t*1000;
		unsigned long x = (diff*1000)/(t);
		//Serial.print(diff*1000);
		//Serial.print("-");
		//Serial.print(t);
		//Serial.print("-");
		//Serial.print(x);
		//Serial.print("-");
		percent = float(float(x)/float(1000));
		//Serial.println(percent);
		_currentTime = _time - diff / 1000;
   //Serial.println(_currentTime);
	}

	if (_currentTime > 0) {
		display();

		//Serial.print(" c:");
		//Serial.print(_currentTime);
		//Serial.print(" m:");
		//Serial.print(millis());
		//Serial.print(" d:");
		//Serial.println(diff);


	} else {
		if (!_finished) {
			_currentTime = 0;
			_finished = true;
			displayFinished();
      doAction.strike();
		}
	}

	if (b != ClickEncoder::Open) {
		switch (b) {
		case ClickEncoder::Clicked:
			doAction.out();
			_nextState = 0;
			break;
		}
	}
	_last = rotaryValue;

}

void Timer::start(int16_t rotaryValue, uint16_t zeit) {
  Serial.println("Start");
	_nextState = 255;
	_finished = false;
	_time = zeit;
	_currentTime = zeit;
	percent = 0;
	_last = rotaryValue;
	_startMillis = millis();
	Serial.print(_time);
	//teeServo.in();
}

byte Timer::nextState() {
	return _nextState;
}

void Timer::display() {
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SSD1306_WHITE);

	  displayTime.show(_currentTime, _display);
  	byte w = 128 * percent;
    _display->fillRect(0, 0, w, 5, SSD1306_WHITE);
    _display->display();
}

void Timer::displayFinished() {

    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SSD1306_WHITE);
    _display->setCursor(4, 13);
    _display->print("Finished");
    _display->display();

}
