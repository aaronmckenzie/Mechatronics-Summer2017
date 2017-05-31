void setup() {
  // put your setup code here, to run once:
pinMode (2,OUTPUT);
pinMode (4,OUTPUT);
pinMode (6,OUTPUT);

analogWrite (6,50);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (2, HIGH);
  digitalWrite (4, LOW);
  delay(1000);                       // wait for a second
  
  digitalWrite (2, LOW);
  digitalWrite (4, LOW);
  delay(1000);                       // wait for a second

  digitalWrite (2, LOW);
  digitalWrite (4, HIGH);
  delay(1000);                      // wait for a second

  digitalWrite (2, LOW);
  digitalWrite (4, LOW);
  delay(1000);                       // wait for a second


}


