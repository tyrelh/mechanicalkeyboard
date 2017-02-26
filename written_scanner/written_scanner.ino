//#include <Bounce2.h>
//#include "keycode.h"
#include "Button.h"

// Row pins: 0 1 2 3 4 (5 total)
// Col pins: 5 6 7 8 9 10 11 12 13 14 15 16 17 18 (14 total)

// Define Pins
#define ROW1  0
#define ROW2  1
#define ROW3  2
#define ROW4  3
#define ROW5  4

#define COL1  5
#define COL2  6
#define COL3  7
#define COL4  8
#define COL5  9
#define COL6  10
#define COL7  11
#define COL8  12
#define COL9  13
#define COL10 14
#define COL11 15
#define COL12 16
#define COL13 17
#define COL14 18

#define LED 19

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

// Number of rows and cols
#define ROWS 5
#define COLS 14

// Matrix of Buttons
Button buttons[ROWS][COLS] = {
   {key_1, key_2, key_3}
};

// Matrix of row and col pins
int matrix[ROWS][COLS + 1] = {
   {ROW1, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14},
   {ROW2, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14},
   {ROW3, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14},
   {ROW4, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14},
   {ROW5, COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8, COL9, COL10, COL11, COL12, COL13, COL14},
};

// Register of key values currently pressed
Button currentlyPressed[10] = {

}

void setup() {

   // Setup rows as output, set high
   for (byte i = 0; i < ROWS; i++) {
      pinMode(matrix[i][0], OUTPUT);
      digitalWrite(matrix[i][0], HIGH);
   }

   // Setup cols as inputs, use internal pullup
   for (byte i = 1; i <= COLS; i++) {
      pinMode(matrix[0][i], INPUT_PULLUP);
   }
}

void loop() {
   // Updates the Button objects with their current state
   getKeyState();
   // Checks Button object state and sets registers with values accordingly
   setRegisters(); // todo
   // Pushes the register to the PC
   //pushKeyValues(); // todo

   // button1.update();
   // if (button1.fell()) {
   //   Keyboard.set_modifier(HID_KEY_CONTROL_LEFT);
   // }
   // else if (button1.rose()) {
   //   Keyboard.set_modifier(0);
   // }
   //
   // button2.update();
   // if (button2.fell()) {
   //   Keyboard.set_key1(HID_KEY_C);
   //   Keyboard.send_now();
   // }
   // else if (button2.rose()) {
   //   Keyboard.set_key1(0);
   //   Keyboard.send_now();
   // }
   //
   // button3.update();
   // if (button3.fell()) {
   //   Keyboard.set_key1(HID_KEY_V);
   //   Keyboard.send_now();
   // }
   // else if (button3.rose()) {
   //   Keyboard.set_key1(0);
   //   Keyboard.send_now();
   // }

   //0x43

}

void getKeyState() {
   // scan each ROW
   for (byte i = 0; i < ROWS; i++) {
      // set current ROW to LOW for scan
      digitalWrite(matrix[i][0], LOW);
      // scan each COL in ROW i
      for (byte j = 1; j < COLS + 1; j++) {
         // if button at matrix[i][j] is pressed
         if (digitalRead(matrix[i][j]) == LOW) {
            buttons[i][j - 1].pressed();
         }
         // if button at matrix[i][j] is released();
         else if (digitalRead(matrix[i][j]) == HIGH) {
            buttons[i][j - 1].released();
         }
         // if (buttons[i][j - 1].getState() == true) {
         //    Keyboard.set_key1(buttons[i][j - 1].getValue());
         //    Keyboard.send_now();
         //    digitalWrite(LED, HIGH);
         // } else if (buttons[i][j - 1].getState() == false) {
         //    Keyboard.set_key1(0);
         //    Keyboard.send_now();
         //    digitalWrite(LED, LOW);
         // }
      }
      digitalWrite(matrix[i][0], HIGH);
   }
}

void setRegisters() {
   // Six alpha-numeric or single use keys can be pressed at once
      // currentlyPressed[] indicies 0 - 5
   // Four modifier keys can be pressed at once
      // currentlyPressed[] indicies 6 - 9

   // Loop through all buttons
   for (byte i = 0; i < ROWS; i++) {
      for (byte j = 0; j < COLS; j++) {
         // If key is pressed
         if (buttons[i][j].getState()) {
            boolean alreadyPressed = false;
            // Scan register to see if key is already pressed
            for (byte k = 0; k < 9; k++) {
               // Compare key value to values in register
               if (currentlyPressed[k] == buttons[i][j].getValue()) {
                  alreadyPressed = true;
               }
            }
            // If the key is NOT already pressed
            if (!alreadyPressed) {
               // Look for an empty space in the register
               for (byte k = 0; k < 9; k++) {
                  // If an empty space is found, insert key value
                  if (currentlyPressed[k] == 0) {
                     currentlyPressed[k] = buttons[i][j].getValue();
                     break;
                  }
               }
               // If alreadyPressed is full, key will not be sent
            }
            // If the key is already pressed, nothing needs to be changed
         }
         // If key is NOT pressed
         else if (!(buttons[i][j].getState()) {
            boolen alreadyPressed = false;
            // Scan register to see if key is already pressed
            for (byte k = 0; k < 9; k++) {
               // Compare key value to values in register
               if (currentlyPressed[k] == buttons[i][j].getValue())
               alreadyPressed = true;
            }
            // If the key was previously pressed, needs to be removed from the register
            if (alreadyPressed) {
               // Look for key value in the register
               for (byte k = 0; k < 9; k++) {
                  // If the key value is found in the register, remove it
                  if (currentlyPressed[k] == buttons[i][j].getValue()) {
                     currentlyPressed[k] = 0;
                     break;
                  }
                  // If key value is NOT already in the register, then nothing needs to be changed
               }
            }
         }
      }
   }
}
