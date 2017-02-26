#include "Arduino.h"

class Button {
  public:
    Button(byte row, byte col, char value);

    void setRow(byte row);
    void setCol(byte col);
    byte getRow();
    byte getCol();

    void setState(boolean state);
    boolean getState();
    
    void pressed();
    void released();

    char getValue();

  private:
    char _value;
    byte _row, _col;
    boolean _depressed;

};

Button::Button(byte row, byte col, char value) {
  _row = row;
  _col = col;
  _value = value;
  _depressed = false;
  }

void Button::setRow(byte row) {
    _row = row;
  }

byte Button::getRow() {
  return _row;
}

void Button::setCol(byte col) {
    _col = col;
  }

byte Button::getCol() {
  return _col;
}

void Button::setState(boolean state) {
  _depressed = state;
}
boolean Button::getState() {
  return _depressed;
}

void Button::pressed() {
  _depressed = true;
}

void Button::released() {
  _depressed = false;
}

char Button::getValue() {
  return _value;
}
