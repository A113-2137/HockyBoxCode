#include <Servo.h> //imports the servo library

Servo myservo1; //Declares servos 1-4
Servo myservo2;
Servo myservo3;
Servo myservo4;

int potpin1 = 0; //Adresses 4 pots to analog 0-3
int potpin2 = 1;
int potpin3 = 2;
int potpin4 = 3;

int val1 = 0; //creates 4 blank variabls to be used later
int val2 = 0;
int val3 = 0;
int val4 = 0;

//int val0 = 0;

const int switchPin11 = 2; //names 8 digital pins after the switch they attach to
const int switchPin12 = 3;
const int switchPin21 = 4;
const int switchPin22 = 5;
const int switchPin31 = 7;
const int switchPin32 = 8;
const int switchPin41 = 12;
const int switchPin42 = 13;

int switchState11 = 0; //makes each switch state a blank slate
int switchState12 = 0;
int switchState21 = 0;
int switchState22 = 0;
int switchState31 = 0;
int switchState32 = 0;
int switchState41 = 0;
int switchState42 = 0;

void setup() {

  myservo1.attach(6); //Ataches each servo to a PWM pin, is atached to a motor controler instad of a servo
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);

  pinMode(switchPin11, INPUT_PULLUP); //sets each switch state to a input
  pinMode(switchPin12, INPUT_PULLUP);
  pinMode(switchPin21, INPUT_PULLUP);
  pinMode(switchPin22, INPUT_PULLUP);
  pinMode(switchPin31, INPUT_PULLUP);
  pinMode(switchPin32, INPUT_PULLUP);
  pinMode(switchState41, INPUT_PULLUP);
  pinMode(switchState42, INPUT_PULLUP);
}

void loop() {

  val1 = analogRead(potpin1); //tells each variable to read a pot
  val2 = analogRead(potpin2);
  val3 = analogRead(potpin3);
  val4 = analogRead(potpin4);
  
  switchState11 = digitalRead(switchPin11); //links each switch state to its digital pin *the number in the tens place (12) is the switch number 1-4, the number in the ones place (12) is the switch state, 1 = up, 2 = down*
  switchState12 = digitalRead(switchPin12); //                                                                          ^                                                            ^
  switchState21 = digitalRead(switchPin21);
  switchState22 = digitalRead(switchPin22);
  switchState31 = digitalRead(switchPin31);
  switchState32 = digitalRead(switchPin32);
  switchState41 = digitalRead(switchPin41);
  switchState42 = digitalRead(switchPin42);


  if (switchState11 == HIGH && switchState12 == LOW) { //if switch one is switched up, then set motor one to only go forward
    val1 = map(val1, 0, 1023, 90, 179);
    myservo1.write(val1);
  } else if (switchState11 == HIGH && switchState12 == HIGH) { //if switch one is switched to the middle, then stop motor one
    val1 = 90;
    myservo1.write(val1);
  } else if (switchState11 == LOW && switchState12 == HIGH) { //if switch one is switched down, then set motor one to go both directions
    val1 = map(val1, 0, 1023, 0, 179);
    myservo1.write(val1);
  }

//Serial.println(switchState11); //used to test pots and switches !slows program down!

  if (switchState21 == HIGH && switchState22 == LOW) { //if switch two is switched up, then set motor two to only go forward
    val2 = map(val2, 0, 1023, 90, 179);
    myservo2.write(val2);
  } else if (switchState21 == HIGH && switchState22 == HIGH) { //if switch two is switched to the middle, then stop motor two
    val2 = 90;
    myservo2.write(val2);
  } else if (switchState21 == LOW && switchState22 == HIGH) { //if switch two is switched down, then set motor two to motor one
    myservo2.write(val1);
    
  }


  if (switchState31 == HIGH && switchState32 == LOW) { //if switch three is switched up, then set motor three to only go forward
    val3 = map(val3, 0, 1023, 90, 179);
    myservo3.write(val3);
  } else if (switchState31 == HIGH && switchState32 == HIGH) { //if switch three is switched to the middle, then stop motor three
    val3 = 90;
    myservo3.write(val3);
  } else if (switchState31 == LOW && switchState32 == HIGH) { //if switch three is switched down, then set motor three to motor one
    myservo3.write(val1);
  }

  
  
  if (switchState41 == HIGH && switchState42 == LOW) { //if switch four is switched up, then set motor four to only go forward
    val4 = map(val4, 0, 1023, 90, 179);
    myservo4.write(val4);
  } else if (switchState41 == HIGH && switchState42 == HIGH) { //if switch four is switched to the middle, then stop motor four
    val4 = 90;
    myservo4.write(val4);
  } else if (switchState41 == LOW && switchState42 == HIGH) { //if switch four is switched down, then set motor four to motor one
    myservo4.write(val1);
  }
   // delay(15);
}
