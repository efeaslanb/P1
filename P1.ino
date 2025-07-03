#include <LiquidCrystal.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


const int trigPin = 9;
const int echoPin = 10;
const int relayPin = 11; // Relay control pin


long duration;
int distanceCm, distanceInch;


void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Fan off to start
}


void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;


  if (distanceCm <= 30) {
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distanceCm);
    lcd.print("  cm   ");


    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distanceInch);
    lcd.print("inch ");


    if (distanceCm <= 15) {
      digitalWrite(relayPin, HIGH); // Turn fan ON
    } else {
      digitalWrite(relayPin, LOW); // Turn fan OFF
    }


  } else {
    lcd.setCursor(0, 0);
    lcd.print("Out of range     ");
    lcd.setCursor(0, 1);
    lcd.print("Max: 30cm        ");
    digitalWrite(relayPin, LOW); // Ensure fan is off
  }


  delay(200);
}


