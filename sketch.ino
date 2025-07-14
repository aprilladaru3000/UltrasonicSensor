#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int triggerPin = 7;
const int echoPin = 8;
const int Red = 3;
const int Yellow = 4;
const int Green = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2);

long bacaJarak(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);  // Add a short delay

  long duration = pulseIn(echoPin, HIGH);
  long jarak = (duration * 0.0343) / 2;
  return jarak;
}

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int cm = bacaJarak(triggerPin, echoPin);
  Serial.print(cm);
  Serial.println(" cm");
  delay(100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(cm);
  lcd.print(" cm");

  if (cm > 15) {
    digitalWrite(Green, HIGH);
    digitalWrite(Yellow, LOW);
    digitalWrite(Red, LOW);
  } else if (cm >= 5 && cm <= 15) {
    digitalWrite(Green, LOW);
    digitalWrite(Yellow, HIGH);
    digitalWrite(Red, LOW);
  } else if (cm < 5) {
    digitalWrite(Green, LOW);
    digitalWrite(Yellow, LOW);
    digitalWrite(Red, HIGH);
  }

  delay(1000);
}
