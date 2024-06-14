// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//   
// test 
int onboardLedPin = 32;
int leftBlinkPin = 13;
int rightBlinkPin = 18;

int irLeft = 15;
int irRight = 16;

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
  if (digitalRead(irLeft) || digitalRead(irRight)){
    digitalWrite(onboardLedPin, HIGH);
  } else{
    digitalWrite(onboardLedPin, LOW);
  }

  
  if (timer < 250){
    digitalWrite(mLeftDir, HIGH);
    digitalWrite(mRightDir, HIGH);
    analogWrite(mLeftSpeed, 0);
    analogWrite(mRightSpeed, 0);
  } else if (timer >= 250 && timer < 500){
    digitalWrite(mLeftDir, HIGH);
    digitalWrite(mRightDir, HIGH);
    analogWrite(mLeftSpeed, 127);
    analogWrite(mRightSpeed, 127);
  }


  if (timer > 1000){
    timer = 0;
  } else{
    timer++;
  }
  delay(1);

}
