//
// Hello world!
// This program will make the pathfinder robot move forwards
// for one second, stop for one second, then repeat, forever.
//

// These are the pins for the motor driver board. There are two 
// pins per wheel, one for the direction, and the other for speed.
int mLeftDir = 9;
int mLeftSpeed = 10;
int mRightDir = 11;
int mRightSpeed = 12;

// Setup all of our pins to be outputs.
// Everything inside the curly braces ({ ... }) of the setup function runs ONCE.
void setup() {
  pinMode(mLeftDir, OUTPUT);
  pinMode(mLeftSpeed, OUTPUT);
  pinMode(mRightDir, OUTPUT);
  pinMode(mRightSpeed, OUTPUT);
}

// Everything inside the curly braces ({ ... }) of the loop function runs FOREVER.
void loop() {

  // Here is our code to make the rover move. First we need to set the direction for each motor. 
  // HIGH is forwards, LOW is backwards. Then we set the speed of each motor from 0 - 255. 
  // 0 is stopped, 255 is full speed, 127 is half speed, etc..

  // STOP the motors, doesn't matter which direction
  digitalWrite(mLeftDir, LOW);
  digitalWrite(mRightDir, LOW);
  analogWrite(mLeftSpeed, 0);
  analogWrite(mRightSpeed, 0);

  // Wait for 1000 milliseconds (1 second)
  delay(1000);

  // START the motors at 50% speed going forwards
  digitalWrite(mLeftDir, LOW);
  digitalWrite(mRightDir, HIGH);
  analogWrite(mLeftSpeed, 127);
  analogWrite(mRightSpeed, 127);

  // Wait for 1000 milliseconds (1 second)
  delay(1000);
}
