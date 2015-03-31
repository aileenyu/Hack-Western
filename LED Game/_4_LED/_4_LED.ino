#define ADAM  75
#define FIRST_BUTTON_PIN 2
#define FIRST_LED_PIN 8
#define alarm 12
#define signal 7

int light[4];
int counter = 0;
int active, nextButton;
bool hasPressed = false;
bool finished = true;

void setup() {
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, LOW);
  pinMode(signal, INPUT);
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i=FIRST_BUTTON_PIN; i < FIRST_BUTTON_PIN + 4; i++){
    pinMode(i, INPUT);
  }
  for (int ledNo = FIRST_LED_PIN; ledNo < FIRST_LED_PIN + 4; ledNo++) {
    pinMode(ledNo, OUTPUT);
  }
  randomize();
}
void randomize() {
  for (int i = 0; i < 4; i++) {
    light[i] = FIRST_LED_PIN + random(0, 4);
  }
}

void allOn() {
  for (int i = FIRST_LED_PIN; i < FIRST_LED_PIN+4; i++) {
    analogWrite(i, 255);
  }
}

void allOff() {
  for (int i = FIRST_LED_PIN; i < FIRST_LED_PIN+4; i++) {
    analogWrite(i, 0);
  }
}

void ledStuff() {
  if (counter > ADAM) {
    counter = 0;
    if (active >= 4) {
      active = 0;
      allOff();
    }
    else {
      analogWrite(light[active], 255);
      active++;

    }
  }
  else if (counter > ADAM - 35) {
    allOff();
  }
}

bool pressed(int pin) {
  return digitalRead(pin) == HIGH;
}

void dobutton(int button) {
  if (button == light[nextButton]-FIRST_LED_PIN) {
    nextButton++;
    if (nextButton >= 4) {
      snooze();
    }
  }
  else {
    nextButton = 0;
    allOn();
    active = 0;
    randomize();
    counter = 0;
  }
}

void activateAlarm(){
 digitalWrite(alarm, HIGH);
 finished = false; 
}

void snooze() {
  //TODO implement spark core functionality to turn off alarm
  finished = true;
  allOn();
  delay(200);
  allOff();
  delay(200);
  allOn();
  delay(200);
  allOff();
  digitalWrite(alarm, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (finished){
    allOff();
    if (digitalRead(signal) == HIGH){
      activateAlarm(); 
    }
    return;
  }
  
  ledStuff();
  bool anyPressed = false;
  
  for (int pin = FIRST_BUTTON_PIN; pin < FIRST_BUTTON_PIN+4; pin++) {
    if (pressed(pin)) {
      if (!hasPressed) {
        dobutton(pin - FIRST_BUTTON_PIN);
        hasPressed = true;
      }
      anyPressed = true;
      break;
    }
  }
  
  if (!anyPressed){
    hasPressed = false;
    
  }

  counter++;
  delay(10);
}
