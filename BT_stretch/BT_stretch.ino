// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//   
// test 

#include <SerialBT.h>

int onboardLedPin = 32;
int leftBlinkPin = 13;
int rightBlinkPin = 18;

int irLeft = 4;
int irRight = 5;

int mLeftDir = 9;
int mLeftSpeed = 10;
int mRightDir = 11;
int mRightSpeed = 12;

int timer = 0;

void setup() {
  pinMode(onboardLedPin, OUTPUT);
  pinMode(leftBlinkPin, OUTPUT);
  pinMode(rightBlinkPin, OUTPUT);

  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);

  pinMode(mLeftDir, OUTPUT);
  pinMode(mLeftSpeed, OUTPUT);
  pinMode(mRightDir, OUTPUT);
  pinMode(mRightSpeed, OUTPUT);

  SerialBT.begin();

}

int angry_brightness = 0;
int setAngryEyes = false;
void loop() {

  if (SerialBT) {
    while (SerialBT.available()) {
      char c = SerialBT.read();
      if(c == 'a') {
        setAngryEyes = true;
      } else if (c == 'h') {
        setAngryEyes = false;
      }
      SerialBT.print("Received:");
      SerialBT.write(c);
      SerialBT.println(" ");
    }
  }
  // Use Timer to make eyes grow brighter for first half second
  if (setAngryEyes==true) {

    if (timer < 500){
      angry_brightness = timer/2;
    // then grow dimmer for last half second
    } else{
      angry_brightness = (1000 - timer)/2;
    }
    analogWrite(leftBlinkPin, angry_brightness);
    analogWrite(rightBlinkPin, angry_brightness);
  } else {
    // Blink the left and right LEDs in an alternating sequence every 1 second
    if (timer < 500){
      digitalWrite(leftBlinkPin, HIGH);
      digitalWrite(rightBlinkPin, LOW);
    } else{
      digitalWrite(leftBlinkPin, LOW);
      digitalWrite(rightBlinkPin, HIGH);  
    }
  }



  // Indicator for IR sensors on Pico
  // If either of the IR proximity sensors detect an object, turn the builtin LED on the Pico on
  if (digitalRead(irLeft)){
    digitalWrite(onboardLedPin, HIGH);
  } else if (digitalRead(irRight)) {
    digitalWrite(onboardLedPin, HIGH);
  } else {
    digitalWrite(onboardLedPin, LOW);
  }

  // Turning logic:
  //If left but not right, turn right
  if (digitalRead(irLeft) && !digitalRead(irRight)){
    rover_right();
  //If not left but right, turn left
  } else if (!digitalRead(irLeft) && digitalRead(irRight)) {
    rover_left();
  //Otherwise drive straight
  } else {
    rover_staight();
  }

  
// Old timer driving logic
//   if (timer < 250){
//     rover_stop();
//   } else if (timer >= 250 && timer < 500){
//     rover_staight();
//   }


  if (timer > 1000){
    timer = 0;
  } else{
    timer++;
  }
  delay(1);

}


void rover_stop() {
    digitalWrite(mLeftDir, HIGH);
    digitalWrite(mRightDir, HIGH);
    analogWrite(mLeftSpeed, 0);
    analogWrite(mRightSpeed, 0);
}

void rover_staight() {
    digitalWrite(mLeftDir, HIGH);
    digitalWrite(mRightDir, HIGH);
    analogWrite(mLeftSpeed, 127);
    analogWrite(mRightSpeed, 127);
}

void rover_right() {
    digitalWrite(mLeftDir, LOW);
    digitalWrite(mRightDir, HIGH);
    analogWrite(mLeftSpeed, 127);
    analogWrite(mRightSpeed, 127);
}

void rover_left() {
    digitalWrite(mLeftDir, HIGH);
    digitalWrite(mRightDir, LOW);
    analogWrite(mLeftSpeed, 127);
    analogWrite(mRightSpeed, 127);
}
