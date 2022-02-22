#include <Keyboard.h>
#include <KeyboardLayout.h>

struct Button {
  int GND;
  int PIN;
  int pressed;
};

const int  N_FRETS = 5;
const int  N_BUTTONS = 8;

Button start, strumUp, strumDn, frets[N_FRETS];
Button* buttons[N_BUTTONS];
char keycodes[N_BUTTONS];

const int strumGND = 23;
const int strum1 = 22;
const int strum2 = 21;

void clearPins(){
  for(int i = 0 ; i < 20; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void updateButton(Button *button){
  clearPins();
  pinMode(button->GND, OUTPUT);
  pinMode(button->PIN, INPUT_PULLUP);
  button->pressed = !digitalRead(button->PIN);
}

void updateStrum(){
 clearPins();
 pinMode(strumGND, OUTPUT);
 pinMode(strum1, INPUT_PULLUP);
 pinMode(strum2, INPUT_PULLUP);
 strumUp.pressed = !digitalRead(strum1);
 strumDn.pressed = !digitalRead(strum2);
}


void debugPrint(){
  Serial.print("Start: ");
  Serial.print(start.pressed);
  Serial.print('\t');
  Serial.print("StrumUp: ");
  Serial.print(strumUp.pressed);
  Serial.print('\t');
  Serial.print("StrumDm: ");
  Serial.print(strumDn.pressed);
  Serial.print('\t');
  Serial.print("Green: ");
  Serial.print(frets[0].pressed);
  Serial.print('\t');
  Serial.print("Red: ");
  Serial.print(frets[1].pressed);
  Serial.print('\t');
  Serial.print("Yellow: ");
  Serial.print(frets[2].pressed);
  Serial.print('\t');
  Serial.print("Blue: ");
  Serial.print(frets[3].pressed);
  Serial.print('\t');
  Serial.print("Orange: ");
  Serial.print(frets[4].pressed);
  Serial.println();
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  clearPins();
  for(int i = 0; i < N_FRETS; i++){
    buttons[i] = &frets[i];
  }
  buttons[5] = &strumUp;
  buttons[6] = &strumDn;
  buttons[7] = &start; 
  
  keycodes[0] = 'g';
  keycodes[1] = 'f';
  keycodes[2] = 'd';
  keycodes[3] = 's';
  keycodes[4] = 'a';
  keycodes[5] = '[';
  keycodes[6] = ']';
  keycodes[7] = 't';
  
  start.GND = 12;
  start.PIN = 11;
  start.pressed = 0;
  
  strumUp.GND = 23;
  strumUp.PIN = 22;
  strumUp.pressed = 0;
  strumDn.GND = 23;
  strumDn.PIN = 21;
  strumDn.pressed = 0;

  frets[0].GND = 9;
  frets[0].PIN = 5;
  
  frets[1].GND = 2;
  frets[1].PIN = 6;
  
  frets[2].GND = 2;
  frets[2].PIN = 4;
  
  frets[3].GND = 2;
  frets[3].PIN = 8;
  
  frets[4].GND = 3;
  frets[4].PIN = 7;

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop(){
//  delay(100);
  updateButton(&start);
  updateStrum();
  for(int i = 0; i < N_FRETS; i++){
    updateButton(&frets[i]);
  }
  
  for(int i = 0; i < N_BUTTONS; i++){
    if (buttons[i]->pressed){
        Keyboard.press(keycodes[i]);
    } else
        Keyboard.release(keycodes[i]);
  }
 
  //debugPrint();
}
