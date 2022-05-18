#include "Arduino.h"
#include "Menu.h"
#include <ClickEncoder.h>

#include "DisplayTime.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

Menu::Menu(Adafruit_SSD1306 *display) :
		_last(0), _menuPosition(1), _maxMenuItems(2), _nextState(255), t(false), previousMillis(
				0) {
          _display = display;
}

void Menu::refresh(int16_t rotaryValue, ClickEncoder::Button b) {
	//Serial.println("Refresh:");
	if (rotaryValue != _last) {
		if (_last > rotaryValue) {
			_menuPosition--;
		} else {
			_menuPosition++;
		}
		if (_menuPosition < 1) {
			_menuPosition = _maxMenuItems;
		}
		if (_menuPosition > _maxMenuItems) {
			_menuPosition = 1;
		}

		//display();
	}

	display();

	if (b != ClickEncoder::Open) {
		switch (b) {
		case ClickEncoder::Clicked:
			switch (_menuPosition) {
			case 1:
				_nextState = 1;
				break;
			case 2:
				_nextState = 2;

				break;
			case 3:
				_nextState = 3;
				break;
			case 4:
				_nextState = 4;
				break;
			}
			break;
		}
	}
	_last = rotaryValue;

}

void Menu::start(int16_t rotaryValue, uint16_t zeit) {
	previousMillis = millis();
	_last = rotaryValue;
	_menuPosition = 1;
	_nextState = 255;
  _time = zeit;
	display();
	//Serial.println("Start");
	//Serial.println(_last);
}

byte Menu::nextState() {
	return _nextState;
}

void Menu::display() {
  _display->clearDisplay();
  _display->setFont(&FreeSans9pt7b);
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(4, 13);
  _display->print("Start");
  _display->setCursor(4, 28);
  _display->print("Dauer");
//  _display->setCursor(4, 43);
//  _display->print("Zeit 1");
//  _display->setCursor(4, 58);
//  _display->print("Zeit 2");
  displayTime.showTimeInMenu(_time,_display, SSD1306_INVERSE);
  _display->fillRect(0, (_menuPosition - 1) * 15, 128, 15, SSD1306_INVERSE);
  _display->display();
}

void Menu::drawBitmap(uint8_t * bitArray) {
	//uint8_t *screenmemory = uView.getScreenBuffer();
	//for (int i=0; i<(64 * 48 / 8); i++)
	//screenmemory[i] = bitArray[i];
}
