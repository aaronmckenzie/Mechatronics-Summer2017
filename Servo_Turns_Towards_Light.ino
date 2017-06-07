#include <Servo.h> //Servo Library is included
Servo myServo;

int sensorValue = 0; // variable to store value coming in
int LDR1 = A4;
int LDR2 = A2;
int servo = 7;

void setup() {

  myServo.attach(servo); // servo pin to library

  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
}


void loop() {


  int LDR1_val = analogRead(LDR1);
  int LDR2_val = analogRead(LDR2);

  if (LDR1_val > LDR2_val) //Here we decide in which direction the servo should rotate
  {
    myServo.write(45); //Here we rotate the servo towards the right servo when its value is greater than LDR2
  }
  else if (LDR1_val < LDR2_val) {
    myServo.write(135); //Here we rotate the servo towards the left servo
  }
  else if (LDR1_val = LDR2_val) {
    myServo.write(0); //Here the servo is at neutral when the light readings are equal

  }
}

