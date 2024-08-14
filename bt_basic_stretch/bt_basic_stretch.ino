// 
//   This program will tests all of the lights, sensors, and motors on the line-following robot
//   to make sure all of the wires are hooked up correctly.
//   

#include <SerialBT.h>

int onboardLedPin = 32;

String user_input = "empty for now";

void setup() {
  pinMode(onboardLedPin, OUTPUT);
  digitalWrite(onboardLedPin,HIGH);
  
  SerialBT.begin();
  // while(!SerialBT.available()){delay(100);}
  delay(3000);

}

void loop() {
  
  if (SerialBT) {
    while (SerialBT.available()) {
      user_input = SerialBT.readString(); // Read user input
      user_input.trim();
      
      // Write back to the serial port the character received
      // this helps with debugging
      SerialBT.print("Received:");
      SerialBT.print(user_input);
      SerialBT.println(" ");
    }
  }
  
  if(user_input == "r") {
    digitalWrite(onboardLedPin,HIGH);
  } else if (user_input == "f") {
    digitalWrite(onboardLedPin,LOW);
  } else {
    
  }

  delay(5);

}
