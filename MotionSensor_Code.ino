#include <NewPing.h> // ultrasonic sensor
#include <LiquidCrystal.h> // LCD

LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // initialize lcd object

// sensor variables
const int trigPin = 2;
const int echoPin = 1;
int ledPin = 9;

// LCD variables
int distance; // distance from sensor calculated by duration divided by 2
double duration; // duration of pulse will calculate distance
const int contrast = 60;
String displayMsg;
double displayVal;

void setup() {
  // Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LED light
  pinMode(ledPin, OUTPUT);

  // LCD
  analogWrite(13, contrast);
  lcd.begin(16, 2);
}

void loop() {
  // Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // reads the echo pin and returns sound wave traveled in microseconds
  distance = (duration * 0.034) / 2;
  displayVal = distance; // displayVal set as distance to be displayed on LCD
  displayVal = round(displayVal * 100) / 100; // rounds to 2 decimal places

  // LCD + LED light
  lcd.setCursor(0, 0);
  if (displayVal <= 30.0) {
    digitalWrite(ledPin, HIGH); // led turns on
    displayMsg = "Too Close!!!";

    lcd.print(displayMsg);
  }
  else {
    digitalWrite(ledPin, LOW); // led turns off
    displayMsg = "Good Distance";

    lcd.print(displayMsg);
  }

  // clears 1st row of LCD each iteration (to prevent buggy display)
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
}
