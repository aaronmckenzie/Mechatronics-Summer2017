// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int startHour = 14; //open solenoid at preset hour
int startMinute = 18; // open solenoid at preset minute

const int amountofFlow = 300; //The amount of liquid I want flowing through the system
int flowSet = 0;

int solenoidPin = 12; // Designate pin 12 as the Solenoid


byte sensorInterrupt = 0;  // interrupt 0 is on digital pin 2 (for flow meter)
byte sensorPin  = 2; // Designate pin 2 for flow meter
float calibrationFactor = 4.5; // The hall-effect flow sensor outputs approximately 4.5 pulses per second per litre/minute of flow.
volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;


void setup() {
  pinMode(A3, OUTPUT); // Output for RTC
  pinMode(A2, OUTPUT); // Output for RTC
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);

  while (!Serial); // for Leonardo/Micro/Zero

  pinMode(solenoidPin, OUTPUT);   // Set our Solenoid as an output pin
  digitalWrite(solenoidPin, LOW); // Set the Solenoud to LOW (off)

  Serial.begin(57600);



  if (! rtc.begin()) {

    Serial.println("Couldn't find RTC");
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // Initialize a serial connection for reporting values to the host
  Serial.begin(57600);

  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output

  //Below begins setup for the flow meter

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop() {
  Serial.println();
  Serial.println("Time Below:");

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.println();

  delay(1000);

  if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);

    // Because this loop may not complete in exactly 1 second intervals we calculate the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output based on the number of pulses per second per units of measure (litres/minute in this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

    // Note the time this processing pass was executed. Note that because we've disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();

    flowMilliLitres = (flowRate / 60) * 1000;     // Divide the flow rate in litres/minute by 60 to determine how many litres have passed through the sensor in this 1 second interval, then multiply by 1000 to convert to millilitres.



    totalMilliLitres += flowMilliLitres;  // Add the millilitres passed in this second to the cumulative total

    unsigned int frac;

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.println();

    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min");
    // Print the number of litres flowed in this second
    Serial.print("  Current Liquid Flowing: ");             // Output separator
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");

    // Print the cumulative total of litres flowed since starting
    Serial.print("  Output Liquid Quantity: ");             // Output separator
    Serial.print(totalMilliLitres);
    Serial.println("mL");

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;

    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }

  if (now.hour() == startHour && now.minute() == startMinute) {
    valveOpen();
  } else {
    valveClosed();
  }

  if (totalMilliLitres >= amountofFlow) {      // If the outflow through the meter is equal to or greater than 300ml close the valve
    valveClosed();
    totalMilliLitres  = 0;
  }

}


void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
