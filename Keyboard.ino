
byte rows[] = {2,3,20,4};
byte cols[] = {22,24,23,0,21,1,8,5,6,9,7,11};
bool down[4*12] = {0};
#define NUM_LAYERS 4
#define NUM_KEYS (NUM_LAYERS*4*12)
int keys[NUM_KEYS] = {0};

#define lrc(l,r,c) keys[(l)*4*12 + (r)*12 + (c)]

#define is_mod(k) ((k) <= -1 && (k) >= -4)
#define M_SHIFT -1
#define M_CTRL -2
#define M_ALT -3
#define M_SUPER -4

#define is_special(k) ((k) <= -5 && (k) >= -7)
#define S_FN -5
#define S_LW -6
#define S_RS -7

#define PRINT 0

void setup() {
  pinMode(13, OUTPUT);
  
  for(int i = 0; i < 4; i ++)
    pinMode(rows[i], OUTPUT);
  for(int i = 0; i < 12; i ++)
    pinMode(cols[i], INPUT_PULLUP);

#if PRINT
  Serial.begin(9600);
#endif

  lrc(0,0,0) = KEY_ESC;
  lrc(0,0,1) = KEY_Q;
  lrc(0,0,2) = KEY_W;
  lrc(0,0,3) = KEY_E;
  lrc(0,0,4) = KEY_R;
  lrc(0,0,5) = KEY_T;
  lrc(0,0,6) = KEY_Y;
  lrc(0,0,7) = KEY_U;
  lrc(0,0,8) = KEY_I;
  lrc(0,0,9) = KEY_O;
  lrc(0,0,10) = KEY_P;
  lrc(0,0,11) = KEY_BACKSPACE;
  
  lrc(0,1,0) = KEY_TAB;
  lrc(0,1,1) = KEY_A;
  lrc(0,1,2) = KEY_S;
  lrc(0,1,3) = KEY_D;
  lrc(0,1,4) = KEY_F;
  lrc(0,1,5) = KEY_G;
  lrc(0,1,6) = KEY_H;
  lrc(0,1,7) = KEY_J;
  lrc(0,1,8) = KEY_K;
  lrc(0,1,9) = KEY_L;
  lrc(0,1,10) = KEY_SEMICOLON;
  lrc(0,1,11) = KEY_QUOTE;
  
  lrc(0,2,0) = M_SHIFT;
  lrc(0,2,1) = KEY_Z;
  lrc(0,2,2) = KEY_X;
  lrc(0,2,3) = KEY_C;
  lrc(0,2,4) = KEY_V;
  lrc(0,2,5) = KEY_B;
  lrc(0,2,6) = KEY_N;
  lrc(0,2,7) = KEY_M;
  lrc(0,2,8) = KEY_COMMA;
  lrc(0,2,9) = KEY_PERIOD;
  lrc(0,2,10) = KEY_UP;
  lrc(0,2,11) = KEY_ENTER;

  lrc(0,3,0) = M_CTRL;
  lrc(0,3,1) = M_SUPER;
  lrc(0,3,2) = M_ALT;
  lrc(0,3,3) = S_FN;
  lrc(0,3,4) = S_LW;
  lrc(0,3,5) = lrc(0,3,6) = KEY_SPACE;
  lrc(0,3,7) = S_RS;
  lrc(0,3,8) = KEY_SLASH;
  lrc(0,3,9) = KEY_LEFT;
  lrc(0,3,10) = KEY_DOWN;
  lrc(0,3,11) = KEY_RIGHT;
}

int layer = 0;
int mod = 0;
bool pressed[NUM_KEYS] = {0};

void loop()
{
  digitalWrite(13, LOW);
  for(int r = 0; r < 4; r ++) {      
    for(int c = 0; c < 12; c ++) {
      digitalWrite(rows[r], LOW);
      
      int k = lrc(layer,r,c);
      bool* down = pressed + layer*4*12 + r*12 + c;

      if (digitalRead(cols[c]) == LOW) {
        digitalWrite(13, HIGH);
#if PRINT
        Serial.print(r);
        Serial.print(" ");
        Serial.print(c);
        Serial.print("\n");
#endif
        if (*down) goto _continue;
        *down = 1;
        if (is_special(k)) {
          
        } else if (is_mod(k)) {
          if (k == M_SHIFT) mod = mod ^ MODIFIERKEY_SHIFT;
          if (k == M_CTRL) mod = mod ^ MODIFIERKEY_CTRL;
          if (k == M_ALT) mod = mod ^ MODIFIERKEY_ALT;
          if (k == M_SUPER) mod = mod ^ MODIFIERKEY_GUI;
          Keyboard.set_modifier(mod);
          Keyboard.send_now();
        } else {
          Keyboard.press(k);
        }
      } else {
        if (!*down) goto _continue;
        *down = 0;
        if (is_special(k)) {
          
        } else if (is_mod(k)) {
          if (k == M_SHIFT) mod = mod ^ MODIFIERKEY_SHIFT;
          if (k == M_CTRL) mod = mod ^ MODIFIERKEY_CTRL;
          if (k == M_ALT) mod = mod ^ MODIFIERKEY_ALT;
          if (k == M_SUPER) mod = mod ^ MODIFIERKEY_GUI;
          Keyboard.set_modifier(mod);
          Keyboard.send_now();
        } else {
          Keyboard.release(k);
        }
      }
      _continue:
      digitalWrite(rows[r], HIGH);
    }
  }

  

  delay(50);
}

