int trig = 7;
int echo = 8;
float limit = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long temps = pulseIn(echo, HIGH, 30000);

  float distance = (0.034 * temps)/2;
  Serial.println(distance);

  if (distance > 0 && distance < limit){
    int etat = digitalRead(2);
    if (etat == 0){
      Serial.println("Détecté");
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
    }else{
      Serial.println("Non Détecté");
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
    };
  }else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  };
  delay(1000);
}
