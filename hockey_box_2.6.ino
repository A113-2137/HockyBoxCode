#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int potpin1 = 0;
int potpin2 = 1;
int potpin3 = 2;
int potpin4 = 3;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

int val0 = 0;

const int switchPin11 = 2;
const int switchPin12 = 3;
const int switchPin21 = 4;
const int switchPin22 = 5;
const int switchPin31 = 7;
const int switchPin32 = 8;
const int switchPin41 = 12;
const int switchPin42 = 13;

int switchState11 = 0;
int switchState12 = 0;
int switchState21 = 0;
int switchState22 = 0;
int switchState31 = 0;
int switchState32 = 0;
int switchState41 = 0;
int switchState42 = 0;

void setup() {

  myservo1.attach(6);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);

  pinMode(switchPin11, INPUT_PULLUP);
  pinMode(switchPin12, INPUT_PULLUP);
  pinMode(switchPin21, INPUT_PULLUP);
  pinMode(switchPin22, INPUT_PULLUP);
  pinMode(switchPin31, INPUT_PULLUP);
  pinMode(switchPin32, INPUT_PULLUP);
  pinMode(switchState41, INPUT_PULLUP);
  pinMode(switchState42, INPUT_PULLUP);
}

void loop() {

  val1 = analogRead(potpin1);
  val2 = analogRead(potpin2);
  val3 = analogRead(potpin3);
  val4 = analogRead(potpin4);
  
  switchState11 = digitalRead(switchPin11);
  switchState12 = digitalRead(switchPin12);
  switchState21 = digitalRead(switchPin21);
  switchState22 = digitalRead(switchPin22);
  switchState31 = digitalRead(switchPin31);
  switchState32 = digitalRead(switchPin32);
  switchState41 = digitalRead(switchPin41);
  switchState42 = digitalRead(switchPin42);


  if (switchState11 == HIGH && switchState12 == LOW) {
    val1 = map(val1, 0, 1023, 90, 179);
    myservo1.write(val1);
  } else if (switchState11 == HIGH && switchState12 == HIGH) {
    val1 = 90;
    myservo1.write(val1);
  } else if (switchState11 == LOW && switchState12 == HIGH) {
    val1 = map(val1, 0, 1023, 0, 179);
    myservo1.write(val1);
  }

//Serial.println(switchState11);

  if (switchState21 == HIGH && switchState22 == LOW) {
    val2 = map(val2, 0, 1023, 90, 179);
    myservo2.write(val2);
  } else if (switchState21 == LOW && switchState22 == LOW) {
    val2 = 90;
    myservo2.write(val2);
  } else if (switchState21 == LOW && switchState22 == HIGH) {
    myservo2.write(val1);
    
  }


  if (switchState31 == HIGH && switchState32 == LOW) {
    val3 = map(val3, 0, 1023, 90, 179);
    myservo3.write(val3);
  } else if (switchState31 == LOW && switchState32 == LOW) {
    val3 = 90;
    myservo3.write(val3);
  } else if (switchState31 == LOW && switchState32 == HIGH) {
    myservo3.write(val1);
  }

  
  
  if (switchState41 == HIGH && switchState42 == LOW) {
    val4 = map(val4, 0, 1023, 90, 179);
    myservo4.write(val4);
  } else if (switchState41 == LOW && switchState42 == LOW) {
    val4 = 90;
    myservo4.write(val4);
  } else if (switchState41 == LOW && switchState42 == HIGH) {
    myservo4.write(val1);
  }
   // delay(15);
}
