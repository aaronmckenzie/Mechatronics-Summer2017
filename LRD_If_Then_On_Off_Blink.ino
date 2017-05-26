const int analogPin = A0;    // select the input pin for the potentiometer
const int ledPin = 13;      // select the pin for the LED
const int threshold = 700;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT); // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
 
  int analogValue = analogRead(analogPin);  //read the input on analog pin 0

  
  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    digitalWrite(ledPin, HIGH);      // turn the LED on (HIGH is the voltage level)
  } else if (analogValue > 400){ 
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  } 
  if (analogValue<threshold && threshold<400){
 digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(1000);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(1000);

}
  }
