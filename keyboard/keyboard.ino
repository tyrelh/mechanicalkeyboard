//#include <Bounce2.h>
#include "Button.h"

// Define Pins
#define ROW1 0
#define COL1 1
#define COL2 2
#define COL3 3
#define DEBUG_LED 13

// ROW1 keys
Button key_escape      (1,1,'BLANK');
Button key_1           (1,2,'KEY_RIGHT_SHIFT');
Button key_2           (1,3,'KEY_T');
Button key_3           (1,4,'KEY_2');
//Button key_4           (1,5);
//Button key_5           (1,6);
//Button key_6           (1,7);
//Button key_7           (1,8);
//Button key_8           (1,9);
//Button key_9           (1,10);
//Button key_0           (1,11);
//Button key_minus       (1,12);
//Button key_equals      (1,13);
//Button key_delete      (1,14);

// ROW2 keys
//Button key_tab         (2,1);
//Button key_Q           (2,2);
//Button key_W           (2,3);
//Button key_E           (2,4);
//Button key_R           (2,5);
//Button key_T           (2,6);
//Button key_Y           (2,7);
//Button key_U           (2,8);
//Button key_I           (2,9);
//Button key_O           (2,10);
//Button key_P           (2,11);
//Button key_rightBracket(2,12);
//Button key_leftBracket (2,13);
//Button key_backspace   (2,14);

// ROW3 keys
//Button key_capsLock    (3,1);
//Button key_A           (3,2);
//Button key_S           (3,3);
//Button key_D           (3,4);
//Button key_F           (3,5);
//Button key_G           (3,6);
//Button key_H           (3,7);
//Button key_J           (3,8);
//Button key_K           (3,9);
//Button key_L           (3,10);
//Button key_semiColon   (3,11);
//Button key_apostrophe  (3,12);
//Button key_tilde       (3,13); // key_tilde is physically on ROW1, electrically on ROW3
//Button key_enter       (3,14);

// ROW4 keys
//Button key_leftShift   (4,1);
//Button key_Z           (4,2);
//Button key_X           (4,2);
//Button key_C           (4,3);
//Button key_V           (4,4);
//Button key_B           (4,5);
//Button key_N           (4,6);
//Button key_M           (4,7);
//Button key_comma       (4,8);
//Button key_period      (4,9);
//Button key_forwardSlash(4,10);
//Button key_backSlash   (4,11);
//Button key_upArrow     (4,12);
//Button key_rightShift  (4,13);

// ROW5 keys
//Button key_leftControl (5,1);
//Button key_leftSuper   (5,2);
//Button key_alt         (5,3);
//Button key_space       (5,6);
//Button key_rightSuper  (5,10);
//Button key_hyper       (5,11);
//Button key_leftArrow   (5,12);
//Button key_downArrow   (5,13);
//Button key_rightArrow  (5,14);

#define COLS 3
#define ROWS 1

Button buttons[ROWS][COLS] = {
  {key_1, key_2, key_3}
};

  

int matrix[ROWS][COLS + 1] = {
  {ROW1, COL1, COL2, COL3}
};

void setup() {
pinMode(ROW1, OUTPUT);
  digitalWrite(ROW1, HIGH);
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  pinMode(COL3, INPUT_PULLUP);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, LOW);
  
}

void loop() {
  scan();
 
/*
  button1.update();
  if (button1.fell()) {
    Keyboard.set_modifier(HID_KEY_CONTROL_LEFT);
  }
  else if (button1.rose()) {
    Keyboard.set_modifier(0);
  }

  button2.update();
  if (button2.fell()) {
    Keyboard.set_key1(HID_KEY_C);
    Keyboard.send_now();
  }
  else if (button2.rose()) {
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }

  button3.update();
  if (button3.fell()) {
    Keyboard.set_key1(HID_KEY_V);
    Keyboard.send_now();
  }
  else if (button3.rose()) {
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }

//0x43
*/
}

void scan() {

  // scan each ROW
  for (byte i = 0; i < ROWS; i++) {
    
    // set current ROW to LOW for scan
    digitalWrite(matrix[i][0], LOW);
    
    // scan each COL in ROW i
    for (byte j = 1; j < COLS + 1; j++){
      
      // if button at matrix[i][j] is pressed
      if (digitalRead(matrix[i][j]) == LOW) {
        buttons[i][j - 1].pressed();
      }

      // if button at matrix[i][j] is released();
      else {
        buttons[i][j - 1].released();
      }
      
      if (buttons[i][j - 1].getState() == true) {
        Keyboard.set_key1(buttons[i][j - 1].getValue());
        Keyboard.send_now();
        digitalWrite(DEBUG_LED, HIGH);
      } else if (buttons[i][j - 1].getState() == false) {
        Keyboard.set_key1(0);
        Keyboard.send_now();
        digitalWrite(DEBUG_LED, LOW);
      }
    }
    digitalWrite(matrix[i][0], HIGH);
  }
}
