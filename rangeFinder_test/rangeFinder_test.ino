// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//   
//  *** NOT WORKING YET *** 
int onboardLedPin = 32;
int leftBlinkPin = 13;
int rightBlinkPin = 18;

int irLeft = 4;
int irRight = 5;

int mLeftDir = 6;
int mLeftSpeed = 7;
int mRightDir = 8;
int mRightSpeed = 9;

int trigPin = 1;
int echoPin = 2;

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

  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 

}

int angry_brightness = 0;
void loop() {
  // Use Timer to make eyes grow brighter for first half second
  if (timer < 500){
    angry_brightness = timer/2;
  // then grow dimmer for last half second
  } else{
    angry_brightness = (1000 - timer)/2;
  }
  analogWrite(leftBlinkPin, angry_brightness);
  analogWrite(rightBlinkPin, angry_brightness);


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

    // Code for HC-SR04 Range Finder
    int echoDuration = 0;
    float distance = 0;
    // Start Measurement
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2);  
    digitalWrite(trigPin, HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigPin, LOW);
    // Wait for Echo to come back
    echoDuration = pulseIn(echoPin,HIGH,100);
    distance = (echoDuration*.0343)/2; // Duration / Speed of Sound
    Serial.print("Distance: ");  
	Serial.println(distance);  
  
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
