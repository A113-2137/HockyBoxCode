#include <Servo.h> //imports the servo library
#include <LiquidCrystal_I2C.h> //imports LCD library (for a lcd screen with I2C atached)

Servo myservo1; //Declares servos 1-4
Servo myservo2;
Servo myservo3;
Servo myservo4;

String mtrText1 = "m1:"; //creates initial texts for lcd display
String mtrText2 = "m2:";
String mtrText3 = "m3:";
String mtrText4 = "m4:";

int pmtr1 = 0; //creates 4 blank variables to be used as percents
int pmtr2 = 0;
int pmtr3 = 0;
int pmtr4 = 0;

int potpin1 = A0; //Adresses 4 pots to analog 0-3
int potpin2 = A1;
int potpin3 = A2;
int potpin4 = A3;

LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD SDA is always A4 and SCL is always A5


int val1 = 0; //creates 4 blank variabls to be used later
int val2 = 0;
int val3 = 0;
int val4 = 0;

int motoroff = 89;
float mtr1 = motoroff; //creates 4 servo motor outputs, and sets inital value to 90 = no motion = safe
float mtr2 = motoroff;
float mtr3 = motoroff;
float mtr4 = motoroff;

float mtr1_old = motoroff; //creates 4 servo motor outputs, and sets inital value to 90 = no motion = safe
float mtr2_old = motoroff;
float mtr3_old = motoroff;
float mtr4_old = motoroff;

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

String sw1 = "****";
String sw2 = "****";
String sw3 = "****";
String sw4 = "****";
String sval1 = "****";
String sval2 = "****";
String sval3 = "****";
String sval4 = "****";

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;        // will store last time the servo was updated
unsigned long deltaMillis = 0;
float speedchange;                // Variable to hold the speedchange requested this loop
float maxchangefortime;
float Mtr1_RAMP = 45;           // This sets the max PWM change at 90 units per second, which is zero to full speed in 1 seconds.
unsigned long lastdisplay = 0;
unsigned long displaytime = 0;
String stringout = "****";

void setup() {

  lcd.begin(); // initialize the LCD

  lcd.setBacklight((uint8_t)1); // Turn on the blacklight

  myservo1.attach(6, 998, 2020); //Ataches each servo to a PWM pin, is atached to a motor controler instad of a servo
  myservo2.attach(9, 998, 2020);
  myservo3.attach(10, 1001, 2014);
  myservo4.attach(11, 1001, 2014);

  pinMode(switchPin11, INPUT_PULLUP); //sets each switch state to a input
  pinMode(switchPin12, INPUT_PULLUP);
  pinMode(switchPin21, INPUT_PULLUP);
  pinMode(switchPin22, INPUT_PULLUP);
  pinMode(switchPin31, INPUT_PULLUP);
  pinMode(switchPin32, INPUT_PULLUP);
  // pinMode(switchState41, INPUT_PULLUP); // found you
  //  pinMode(switchState42, INPUT_PULLUP);
  pinMode(switchPin41, INPUT_PULLUP); // found you
  pinMode(switchPin42, INPUT_PULLUP);
}

void loop() {
  Serial.begin(115200); // Start Debugging Data

  val1 = analogRead(potpin1); //tells each variable to read a pot
  sval1 = String(val1);
  val2 = analogRead(potpin2);
  sval2 = String(val2);
  val3 = analogRead(potpin3);
  sval3 = String(val3);
  val4 = analogRead(potpin4);
  sval4 = String(val4);

  switchState11 = digitalRead(switchPin11); //links each switch state to its digital pin *the number in the tens place (12) is the switch number 1-4, the number in the ones place (12) is the switch state, 1 = up, 2 = down*
  switchState12 = digitalRead(switchPin12); //                                                                          ^                                                            ^
  switchState21 = digitalRead(switchPin21);
  switchState22 = digitalRead(switchPin22);
  switchState31 = digitalRead(switchPin31);
  switchState32 = digitalRead(switchPin32);
  switchState41 = digitalRead(switchPin41);
  switchState42 = digitalRead(switchPin42);


  // Calcualte Motor 1

  if (switchState11 == HIGH && switchState12 == LOW)       //if switch one is switched up, then set motor one to go both directions
  {
    mtr1 = map(val1, 1023, 0, 0, 179);
    sw1 = "UP  ";
  }
  else if (switchState11 == LOW && switchState12 == HIGH)  //if switch one is switched down, then set motor one to forward
  {
    mtr1 = map(val1, 1023, 0, 90, 179);
    sw1 = "DOWN";

  }
  else
  {
    mtr1 = motoroff;
    sw1 = "OFF ";
  }


  // Calcualte Motor 2

  if (switchState21 == HIGH && switchState22 == LOW)       //if switch one is switched up, then set motor one to go both directions
  {
    mtr2 = map(val2, 1023, 0, 0, 179);
    sw2 = "UP  ";
  }
  else if (switchState21 == LOW && switchState22 == HIGH)  //if switch one is switched down, follow Motor 1
  {
    mtr2 = mtr1;
    sw2 = "DOWN";
  }
  else
  {
    mtr2 = motoroff;
    sw2 = "OFF ";
  }

  // Calcualte Motor 3

  if (switchState31 == HIGH && switchState32 == LOW)       //if switch one is switched up, then set motor one to go both directions
  {
    mtr3 = map(val3, 1023, 0, 0, 179);
    sw3 = "UP  ";
  }
  else if (switchState31 == LOW && switchState32 == HIGH)  //if switch one is switched down, follow Motor 2
  {
    mtr3 = mtr2;
    sw3 = "DOWN";
  }
  else
  {
    mtr3 = motoroff;
    sw3 = "OFF ";
  }

  // Calcualte Motor 4

  if (switchState41 == HIGH && switchState42 == LOW)       //if switch one is switched up, then set motor one to go both directions
  {
    mtr4 = map(val4, 1023, 0, 0, 179);
    sw4 = "UP  ";
  }
  else if (switchState41 == LOW && switchState42 == HIGH)  //if switch one is switched down, follow Motor 3
  {
    mtr4 = mtr3;
    sw4 = "DOWN";
  }
  else
  {
    mtr4 = motoroff;
    sw4 = "OFF ";
  }


  // Motor Ramping Feature - Allow for motor to ramp to max speed over a second.

  // Determine Max Rate Change for this deltaMillis
  currentMillis = millis();
  deltaMillis = currentMillis - previousMillis;
  maxchangefortime = Mtr1_RAMP * deltaMillis / 1000.0;
  speedchange = abs(mtr1 - mtr1_old);
  /* Serial.print (speedchange);
    Serial.print( "  =>  ");
    Serial.print (maxchangefortime);
    Serial.print( "  =>  ");
    Serial.println (mtr1_old);
    delay(10);
  */
  if (speedchange > maxchangefortime && mtr1 != motoroff) { //Rate Limit needed
    mtr1 = constrain(mtr1, mtr1_old - maxchangefortime, mtr1_old + maxchangefortime);
  }
  else { //Rate Limit Not Needed
  }
  speedchange = abs(mtr2 - mtr2_old);
  if (speedchange > maxchangefortime && mtr2 != motoroff) { //Rate Limit needed
    mtr2 = constrain(mtr2, mtr2_old - maxchangefortime, mtr2_old + maxchangefortime);
  }
  else { //Rate Limit Not Needed
  }
  speedchange = abs(mtr3 - mtr3_old);
  if (speedchange > maxchangefortime && mtr3 != motoroff) { //Rate Limit needed
    mtr3 = constrain(mtr3, mtr3_old - maxchangefortime, mtr3_old + maxchangefortime);
  }
  else { //Rate Limit Not Needed
  }
  speedchange = abs(mtr4 - mtr4_old);
  if (speedchange > maxchangefortime && mtr4 != motoroff) { //Rate Limit needed
    mtr4 = constrain(mtr4, mtr4_old - maxchangefortime, mtr4_old + maxchangefortime);
  }
  else { //Rate Limit Not Needed
  }


  // All Motor Values Calcuated, now send to Motor Controllers.
  myservo1.write(mtr1);
  myservo2.write(mtr2);
  myservo3.write(mtr3);
  myservo4.write(mtr4);

  //Calcualte percents
  pmtr1 = round(((mtr1 - 90) / 90) * 100);
  pmtr2 = round(((mtr1 - 90) / 90) * 100);
  pmtr3 = round(((mtr1 - 90) / 90) * 100);
  pmtr4 = round(((mtr1 - 90) / 90) * 100);

  // Send motor values to LCD
  lcd.setCursor(0,0);
  lcd.print(mtrText1 + pmtr1 + "%   " + mtrText2 + pmtr2 + "%");
  lcd.setCursor(0,1);
  lcd.print(mtrText3 + pmtr3 + "%   " + mtrText4 + pmtr4 + "%");

  // Update OLD values with values just sent
  mtr1_old = mtr1;
  mtr2_old = mtr2;
  mtr3_old = mtr3;
  mtr4_old = mtr4;
  previousMillis = currentMillis;

  //used to test pots and switches !slows program down!
  displaytime = millis() - lastdisplay;
  if  (displaytime > 1000)
  {
    stringout = "SWITCH STATES = " + sw1 + " " + sw2 + " " + sw3 + " " + sw4;
    Serial.println (stringout) ;
    delay(15);
    stringout = "RES VALUES = " + sval1 + "  "  +  sval2 + "  " + sval3 + "  " + sval4;
    Serial.println (stringout) ;
    delay(15);
    Serial.print("MOTOR OUTPUT  = "); Serial.print(mtr1); Serial.print("    "); Serial.print(mtr2); Serial.print("    "); Serial.print(mtr3); Serial.print("    "); Serial.println(mtr4);
    delay(15);
    lastdisplay = millis();

  }

}
