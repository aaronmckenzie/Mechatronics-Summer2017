int sensorPin1 = 7; // select the input pin for the potentiometer
int sensorPin2 = 9; // select the input pin for the potentiometer
int sensorPin3 = 11; // select the input pin for the potentiometer
int sensorValue1 = 0; // variable to store from sensor
int sensorValue2 = 0; // variable to store from sensor
int sensorValue3 = 0; // variable to store from sensor

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:

}

void loop() { // create loop function for sequence
  sensorValue1 = analogRead(sensorPin1); //read from sensor
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  int sensorTotal (sensorValue1 + sensorValue2 + sensorValue3);


  void printAverage();
  Serial.print("Average Sensor Value: ");
  Serial.print(sensorTotal / 3);


}

