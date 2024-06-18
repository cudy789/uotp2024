// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//   
// test 
int onboardLedPin = 32;
int leftBlinkPin = 13;
int rightBlinkPin = 18;

int irLeft = 4;
int irRight = 5;

int mLeftDir = 6;
int mLeftSpeed = 7;
int mRightDir = 8;
int mRightSpeed = 9;

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
  
}

void loop() {
  // Blink the left and right LEDs in an alternating sequence every 1 second
  if (timer < 500){
    digitalWrite(leftBlinkPin, HIGH);
    digitalWrite(rightBlinkPin, LOW);
  } else{
    digitalWrite(leftBlinkPin, LOW);
    digitalWrite(rightBlinkPin, HIGH);  
  }

  // If either of the IR proximity sensors detect an object, turn the builtin LED on the Pico on
  if (digitalRead(irLeft)){
    digitalWrite(onboardLedPin, HIGH);
  } else if (digitalRead(irRight)) {
    digitalWrite(onboardLedPin, HIGH);
  } else {
    digitalWrite(onboardLedPin, LOW);
  }

  
  if (timer < 250){
    rover_stop();
  } else if (timer >= 250 && timer < 500){
    rover_staight();
  }


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
