const int inputPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(inputPin);
  if (val == HIGH)
  {
    Serial.println("HAYDN");
    delay(100);
  } else
  {
    Serial.println("ADAM");
    delay(100);
  }
}
