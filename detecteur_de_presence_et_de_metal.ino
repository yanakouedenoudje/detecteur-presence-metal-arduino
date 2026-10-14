
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinMetal = 2;
const int pinLedMetal = 3;
const int pinLedPlastique = 5;
const int trig = 7;
const int echo = 8;

const float limite = 5.0;

void setup() {
  Serial.begin(9600);

  myservo.attach(9);

  lcd.init();
  lcd.backlight();

  pinMode(pinMetal, INPUT_PULLUP);
  pinMode(pinLedMetal, OUTPUT);
  pinMode(pinLedPlastique, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.write(90);
  lcd.setCursor(0, 0);
  lcd.print("Systeme de tri");
}

void loop() {
  // Mesure de la distance
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long temps = pulseIn(echo, HIGH, 30000);

  if (temps == 0) {
    Serial.println("Aucun echo");
    lcd.setCursor(0, 1);
    lcd.print("Aucun objet     ");

    digitalWrite(pinLedMetal, LOW);
    digitalWrite(pinLedPlastique, LOW);

    delay(200);
    return;
  }

  float distance = (0.0343 * temps) / 2.0;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Dist:");
  lcd.print(distance, 1);
  lcd.print(" cm     ");

  if (distance > 0 && distance < limite) {
    int etat = digitalRead(pinMetal);

    Serial.print("Etat capteur metal : ");
    Serial.println(etat);

    if (etat == LOW) {
      Serial.println("Metal detecte");

      digitalWrite(pinLedMetal, HIGH);
      digitalWrite(pinLedPlastique, LOW);

      myservo.write(0);

      lcd.setCursor(0, 0);
      lcd.print("Metal detecte   ");
    } else {
      Serial.println("Metal non detecte");

      digitalWrite(pinLedMetal, LOW);
      digitalWrite(pinLedPlastique, HIGH);

      myservo.write(180);

      lcd.setCursor(0, 0);
      lcd.print("Plastique       ");
    }
  } else {
    digitalWrite(pinLedMetal, LOW);
    digitalWrite(pinLedPlastique, LOW);
    myservo.write(90);
  }

  delay(2000);
}
