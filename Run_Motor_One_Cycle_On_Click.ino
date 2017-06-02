int pushButton = 7; // designating pin 7 as input

void setup() {

  Serial.begin(9600);
  pinMode(pushButton, INPUT);

  // put your setup code here, to run once:
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
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  delay(1);        // delay in between reads for stability

  // if the button reads anything other than depressed, do not run motors
  if (buttonState < 1) {

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
  }

  // If the button is depressed the motors run through a single cycle of the motors
  else {

    digitalWrite (2, HIGH);
    digitalWrite (4, LOW);
    digitalWrite (8, HIGH);
    digitalWrite (10, LOW);
    delay(1000);                       // wait for a second

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
    delay(1000);                       // wait for a second

    digitalWrite (2, HIGH);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, HIGH);
    delay(1000);                      // wait for a second

    digitalWrite (2, LOW);
    digitalWrite (4, LOW);
    digitalWrite (8, LOW);
    digitalWrite (10, LOW);
    delay(1000);                       // wait for a second
  }

}


