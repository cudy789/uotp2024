void setup() {
  Serial.begin(9600); // sets up the monitor
}

void loop() {
  int sensorValue = analogRead(A1);
  int sensorValue2 = analogRead(A0);
  
  Serial.print(sensorValue); // prints value to the monitor
  Serial.print(","); // prints value to the monitor
  Serial.println(sensorValue2); // prints value to the monitor
}
