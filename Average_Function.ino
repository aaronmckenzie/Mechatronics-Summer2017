void loop() { // create loop function for sequence
  sensorValue1 = analogRead(sensorPin1); //read from sensor
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  int sensorTotal (sensorValue1 + sensorValue2 + sensorValue3);


  void printAverage();
  Serial.print("Average Sensor Value: ");
  Serial.print(sensorTotal / 3);

