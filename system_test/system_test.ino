// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//

  
// These are the pins that the LEDs are hooked up to on the Pico.
int onboardLedPin = 32;
int leftBlinkPin = 13;
int rightBlinkPin = 18;

// These are the pins for the IR proximity sensors.
int irLeft = 4;
int irRight = 5;

// These are the pins for the motor driver board. There are two pins per wheel, one for the direction, and the 
// other for speed.
int mLeftDir = 6;
int mLeftSpeed = 7;
int mRightDir = 8;
int mRightSpeed = 9;

// This variable keeps track of how much time has passed each loop so we can time certain things to happen at 
// specific times (blinking LEDs, moving motors, etc.).
int timer = 0;

// Setup all of our pins to be inputs or outputs.
// Everything inside the curly braces ({ ... }) of the setup function runs ONCE.
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

// Everything inside the curly braces ({ ... }) of the loop function runs FOREVER.
void loop() {
  // Blink the left and right LEDs in an alternating sequence every 1 second
  if (timer < 500){
    digitalWrite(leftBlinkPin, HIGH);
    digitalWrite(rightBlinkPin, LOW);
  } else{
    digitalWrite(leftBlinkPin, LOW);
    digitalWrite(rightBlinkPin, HIGH);  
  }

  // If either of the IR proximity sensors detect an object, turn the builtin LED on the Pico on.
  if (digitalRead(irLeft)){
    digitalWrite(onboardLedPin, HIGH);
  } else if (digitalRead(irRight)) {
    digitalWrite(onboardLedPin, HIGH);
  } else {
    digitalWrite(onboardLedPin, LOW);
  }


  // Move rover in this pattern forever:
  //    stop
  //    straight
  //    turn left
  //    turn right
  if (timer < 250){
    rover_stop();
  } else if (timer >= 250 && timer < 500){
    rover_staight();
  } else if (timer >= 500 && timer < 750){
    rover_left();
  } else if (timer >= 750 && timer < 1000){
    rover_right();
  }


  // This timer variable will count up to 1000. When it hits 1000, reset it to 0.
  // Increase this variable by 1 every 1 millisecond. So this will reach 500 after .5 seconds, 1000 after 1 second, etc..
  if (timer > 1000){
    timer = 0;
  } else{
    timer++;
  }
  delay(1);

}

// Here is our code to make the rover move. First we need to set the direction for each motor. HIGH is forwards, LOW is backwards.
// Then we set the speed of each motor from 0 - 255. 0 is stopped, 255 is full speed, 127 is half speed, etc..
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
