

const int trigPin = 3;
const int echoPin = 5;

const int m1en = 2;
const int m1Dir = 4;
const int m2Dir = 6;

void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  distance = (duration / 2) / 29.1;

  // designate a void distance for print
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range; reading invalid");
    return - 1;
  }
  // designate a void distance for print
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range; reading invalid");

  } else {
    // anything left should be a valid distance
    Serial.print(distance);
    Serial.println(" cm");
  }
  // at less than 20 cm, pause, reverse, pause, pivot, proceed
  if (distance < 20) {

    Pause();
    delay(400);


    //backup
    Backup();
    delay(1000);

    //stop
    Pause();
    delay(400);

    //rotate
    Rotate();
    delay(1000);

    //stop
    Pause();
    delay(400);

  }


  // At distances greater that 20cm away from sensor, have  both motors drive in same direction
  else if ( distance > 20) {

    Forward();

  }

}

