

const int trigPin = 3;
const int echoPin = 5;
const int ledPin = 13;


void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (12, OUTPUT);

  analogWrite (6, 255);
  analogWrite (12, 255);

}

void loop() {

  long duration, distance;
 
  // Drive trigger pin LOW, HIGH, LOW to send the pulse
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); // low for 2 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // high for 10 microseconds
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // measure the time to the echo
  distance = (duration/2) / 29.1; 

  // designate a void distance for print
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range; reading invalid");
      
 } else {
    // anything left should be a valid distance
    Serial.print(distance);
    Serial.println(" cm");

    // at less than 20 cm, pause, reverse, pause, pivot, proceed
  if (distance < 20) { 

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
    delay(400);

    digitalWrite (2, LOW);
    digitalWrite (4, HIGH);
    digitalWrite (8, LOW);
    digitalWrite (10, HIGH);
    delay(1000);

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
    delay(400);

    digitalWrite (2, LOW);
    digitalWrite (4, HIGH);
    digitalWrite (8, HIGH);
    digitalWrite (10, LOW);
    delay(1000);

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
    
    }
 

// At distances greater that 20cm away from sensor, have  both motors drive in same direction
else if ( distance > 20){
    digitalWrite (2, HIGH);
    digitalWrite (4, LOW);
    digitalWrite (8, HIGH);
    digitalWrite (10, LOW);

  }

}
}
