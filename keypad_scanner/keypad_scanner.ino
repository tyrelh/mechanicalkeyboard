#include <Keypad.h>
#include <Adafruit_NeoPixel.h>

// Custom definitions for some keys
#define KEY_SUPER 's'
#define KEY_HYPER 'h'
#define KEY_VOL_UP 'u'
#define KEY_VOL_DOWN 'd'

// Neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 23, NEO_GRB + NEO_KHZ800);

// Electrical grid of keys
const byte ROWS = 5; // Five rows
const byte COLS = 14; // Fourteen columns

// Keymap
char keys[ROWS][COLS] = {
  {KEY_ESC,       KEY_1,    KEY_2,        KEY_3,    KEY_4, KEY_5, KEY_6,    KEY_7, KEY_8,    KEY_9,     KEY_0,        KEY_MINUS,     KEY_EQUAL,      KEY_DELETE},
  {KEY_TAB,       KEY_Q,    KEY_W,        KEY_E,    KEY_R, KEY_T, KEY_Y,    KEY_U, KEY_I,    KEY_O,     KEY_P,        KEY_LEFT_BRACE,KEY_RIGHT_BRACE,KEY_BACKSPACE},
  {KEY_CAPS_LOCK, KEY_A,    KEY_S,        KEY_D,    KEY_F, KEY_G, KEY_H,    KEY_J, KEY_K,    KEY_L,     KEY_SEMICOLON,KEY_QUOTE,     KEY_ENTER,      KEY_TILDE},
  {KEY_LEFT_SHIFT,KEY_Z,    KEY_X,        KEY_C,    KEY_V, KEY_B, KEY_N,    KEY_M, KEY_COMMA,KEY_PERIOD,KEY_SLASH,    KEY_BACKSLASH, KEY_UP,         KEY_PRINTSCREEN},
  {KEY_LEFT_CTRL, KEY_RIGHT_GUI,KEY_RIGHT_ALT,KEY_SPACE,'1',   '2',   KEY_SPACE,'4',   '4',      KEY_SUPER ,KEY_HYPER,    KEY_LEFT,      KEY_DOWN,       KEY_RIGHT},
};

// superLayer Keymap
char superKeys[ROWS][COLS] = {
  {KEY_ESC,       KEY_F1,   KEY_F2,       KEY_F3,   KEY_F4,KEY_F5,KEY_F6,   KEY_F7,KEY_F8,   KEY_F9,    KEY_F10,      KEY_F11,  KEY_F12,     KEY_DELETE},
  {KEY_TAB,       KEY_Q,    KEY_W,        KEY_E,    KEY_R, KEY_T, KEY_Y,    KEY_U, KEY_I,    KEY_O,     KEY_P,        KEY_LEFT_BRACE,KEY_RIGHT_BRACE,KEY_BACKSPACE},
  {KEY_CAPS_LOCK, KEY_A,    KEY_S,        KEY_D,    KEY_F, KEY_G, KEY_H,    KEY_J, KEY_K,    KEY_L,     KEY_SEMICOLON,KEY_QUOTE,     KEY_ENTER,      KEY_TILDE},
  {KEY_LEFT_SHIFT,KEY_Z,    KEY_X,        KEY_C,    KEY_V, KEY_B, KEY_N,    KEY_M, KEY_COMMA,KEY_PERIOD,KEY_SLASH,    KEY_BACKSLASH, KEY_W,         KEY_PRINTSCREEN},
  {KEY_LEFT_CTRL, KEY_RIGHT_GUI,KEY_RIGHT_ALT,KEY_SPACE,'1',   '2',   KEY_SPACE,'4',   '4',      KEY_SUPER ,KEY_HYPER,    KEY_A,      KEY_S,       KEY_D},
};

// hyperLayer Keymap
//char hyperKeys[ROWS][COLS] = {
//  {'1', KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,   '1',       '1', KEY_F11, KEY_F12},
//  {'1', '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',       '1',       '1', '1',     '1'},
//  {'1', '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',       '1',       '1', '1',     '1'},
//  {'1', '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',       '1',       '1', '1',     '1'},
//  {'1', '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    '1',    KEY_SUPER, KEY_HYPER, '1', '1',     '1'}, 
//}

// Pins for rows and columns
byte rowPins[ROWS] = {0,1,2,3,4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,6,7,8,9,10,11,12,14,15,16,17,18,19}; //connect to the column pinouts of the keypad

// Make the Keypad objects
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Keypad superLayer = Keypad(makeKeymap(superKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Adjust keyboard sensitivity
  kpd.setHoldTime(500);
  //superLayer.setHoldTime(300);

  // Debug led
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Light pretty leds
  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(55, 0, 255), 1);
}

void loop() {
  // Fills kpd.key[] array with up-to 6 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys()) {
     // Scan the whole key list.
    for (int i = 0; i < 6; i++) {

      // Check for KEY_SUPER
      if (kpd.key[i].kchar == char(KEY_SUPER)) {
        superLayer.getKeys();

        for (int j = 0; j < 6; j++) {

          switch (superLayer.key[j].kstate) {

            case PRESSED:
              setKeysSuper(j);
              Keyboard.send_now();
              break;

            case HOLD:
              Keyboard.send_now();
              break;

            case RELEASED:
              releaseKeysSuper(j);
              Keyboard.send_now();

            case IDLE:
              break;
          }
        }
      }

      
      // Only find keys that have changed state.
      else if (kpd.key[i].stateChanged) {
        // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
        switch (kpd.key[i].kstate) {

          // Places pressed keys in Keyboard register
          case PRESSED:
            // Shift key modifier pressed
            if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
              Keyboard.set_modifier(MODIFIERKEY_SHIFT);
              Keyboard.send_now();
            }
            // Control key modifier pressed
            else if (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) {
              Keyboard.set_modifier(MODIFIERKEY_CTRL);
              Keyboard.send_now();
            }
            // Alt key modifier pressed
            else if (kpd.key[i].kchar == char(KEY_RIGHT_ALT)) {
              Keyboard.set_modifier(MODIFIERKEY_ALT);
              Keyboard.send_now();
            }
            // GUI key modifier pressed
            else if (kpd.key[i].kchar == char(KEY_RIGHT_GUI)) {
              Keyboard.set_modifier(MODIFIERKEY_GUI);
              Keyboard.send_now();
            }
            // Super key modifier pressed
            //else if (kpd.key[i].kchar == char(KEY_SUPER)) {
              //Keyboard.press(KEY_MEDIA_VOLUME_INC);
              //Keyboard.release(KEY_MEDIA_VOLUME_INC);
            //}
            // Set and send keys
            setKeys(i);
            Keyboard.send_now();
            break;

          // Leaves Keyboard register unchanged
          case HOLD:
            Keyboard.send_now();
            break;

          // Removes keys from the Keyboard register
          case RELEASED:
            // Shift key modifier released
            if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
              Keyboard.set_modifier(0);
              Keyboard.send_now();
            }
            // Control key modifier released
            else if (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) {
              Keyboard.set_modifier(0);
              Keyboard.send_now();
            }
            // Alt key modifier released
            else if (kpd.key[i].kchar == char(KEY_RIGHT_ALT)) {
              Keyboard.set_modifier(0);
              Keyboard.send_now();
            }
            // GUI key modifier released
            else if (kpd.key[i].kchar == char(KEY_RIGHT_GUI)) {
              Keyboard.set_modifier(0);
              Keyboard.send_now();
            }
            // Super key modifier released
            else if (kpd.key[i].kchar == char(KEY_SUPER)) {
              Keyboard.release(KEY_MEDIA_VOLUME_INC);
            }
            // Hyper key modifier released
            else if (kpd.key[i].kchar == char(KEY_HYPER)) {
              Keyboard.release(KEY_MEDIA_VOLUME_DEC);
            }
            // Set and send keys
            releaseKeys(i);
            Keyboard.send_now();
            break;

          // Nothing is happening
          case IDLE:
            break;
        }
      }
    }
  }
}


// Set Keyboard register with keys from kpd layer
void setKeys(int i) {
  if (!((kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) | (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) | (kpd.key[i].kchar == char(KEY_LEFT_CTRL)))) {
    if (i == 0) {
      Keyboard.set_key1(kpd.key[i].kchar);
    } else if (i == 1) {
      Keyboard.set_key2(kpd.key[i].kchar);
    } else if (i == 2) {
      Keyboard.set_key3(kpd.key[i].kchar);
    } else if (i == 3) {
      Keyboard.set_key4(kpd.key[i].kchar);
    } else if (i == 4) {
      Keyboard.set_key5(kpd.key[i].kchar);
    } else if (i == 5) {
      Keyboard.set_key6(kpd.key[i].kchar);
    }
  }
}


// Set Keyboard register with 0's for released keys
void releaseKeys(int i) {
  if (!((kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) | (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) | (kpd.key[i].kchar == char(KEY_LEFT_CTRL)))) {
    if (i == 0) {
      Keyboard.set_key1(0);
    } else if (i == 1) {
      Keyboard.set_key2(0);
    } else if (i == 2) {
      Keyboard.set_key3(0);
    } else if (i == 3) {
      Keyboard.set_key4(0);
    } else if (i == 4) {
      Keyboard.set_key5(0);
    } else if (i == 5) {
      Keyboard.set_key6(0);
    }
  }
}


// Set Keyboard register with keys from super layer
void setKeysSuper(int i) {
  if (!((superLayer.key[i].kchar == char(KEY_LEFT_SHIFT)) | (superLayer.key[i].kchar == char(KEY_LEFT_CTRL)) | (superLayer.key[i].kchar == char(KEY_LEFT_CTRL)))) {
    if (i == 0) {
      Keyboard.set_key1(superLayer.key[i].kchar);
    } else if (i == 1) {
      Keyboard.set_key2(superLayer.key[i].kchar);
    } else if (i == 2) {
      Keyboard.set_key3(superLayer.key[i].kchar);
    } else if (i == 3) {
      Keyboard.set_key4(superLayer.key[i].kchar);
    } else if (i == 4) {
      Keyboard.set_key5(superLayer.key[i].kchar);
    } else if (i == 5) {
      Keyboard.set_key6(superLayer.key[i].kchar);
    }
  }
}


// Set Keyboard register with 0's for released keys
void releaseKeysSuper(int i) {
  if (!((superLayer.key[i].kchar == char(KEY_LEFT_SHIFT)) | (superLayer.key[i].kchar == char(KEY_LEFT_CTRL)) | (superLayer.key[i].kchar == char(KEY_LEFT_CTRL)))) {
    if (i == 0) {
      Keyboard.set_key1(0);
    } else if (i == 1) {
      Keyboard.set_key2(0);
    } else if (i == 2) {
      Keyboard.set_key3(0);
    } else if (i == 3) {
      Keyboard.set_key4(0);
    } else if (i == 4) {
      Keyboard.set_key5(0);
    } else if (i == 5) {
      Keyboard.set_key6(0);
    }
  }
}


// Fill the leds one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}





