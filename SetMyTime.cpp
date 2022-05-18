#include "Arduino.h"
#include "SetMyTime.h"
#include <ClickEncoder.h>

#include "DisplayTime.h"
#include <EEPROMex.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

SetMyTime::SetMyTime(Adafruit_SSD1306 *display) :
		_test(0), _last(0), _nextState(255), _time(10) {
  _display = display;
	Serial.println("SetMyTime");
	//Serial.println(_time);
}

void SetMyTime::refresh(int16_t rotaryValue, ClickEncoder::Button b) {

	if (rotaryValue != _last) {
		/*
		 Serial.print("Refresh:");
		 Serial.print(_last);
		 Serial.print("-");
		 Serial.println(rotaryValue);
		 */
		uint16_t dif = 10;

		if (_time < 30) {
			dif = 1;
		}
		if (_last > rotaryValue) {
			_time -= dif;
		} else {
			_time += dif;
		}
		if (_time < 1) {
			_time = 1;
		}
		if (_time > 2000) {
			_time = 2000;
		}

	}

	if (b != ClickEncoder::Open) {
		switch (b) {
		case ClickEncoder::Clicked:
			_nextState = 0;
			save();
			break;
		}
	}
	display();
	_last = rotaryValue;

}

void SetMyTime::start(int16_t rotaryValue) {
	_nextState = 255;
	_last = rotaryValue;
	_test = rotaryValue;
	_time = EEPROM.readInt(0);
	/*
	 Serial.println("Start: rot");
	 Serial.print(rotaryValue);
	 Serial.print("_last");
	 Serial.print(_last);
	 Serial.println("_test");
	 Serial.println(_test);
	 */
}

byte SetMyTime::nextState() {
	return _nextState;
}

uint16_t SetMyTime::time() {
	_time = EEPROM.readInt(0);
	return _time;
}

void SetMyTime::display() {
    //_display->clearDisplay();
      _display->fillRect(64, 1 * 15, 128, 15, SSD1306_WHITE);
    displayTime.showTimeInMenu(_time,_display, SSD1306_INVERSE);
    _display->display();
}

void SetMyTime::save() {
	EEPROM.updateInt(0, _time);
}
