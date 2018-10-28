#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
Servo myservo3;  // create servo object to control a servo 
Servo myservo4;  // create servo object to control a servo 
 
int potpin0 = 0;  // pot is in 13 pwm analog pin used to connect the potentiometer
int potpin1 = 1;
int potpin2 = 2;
int potpin3 = 3;// analog pin used to connect the potentiometerint val;    // variable to read the value from the analog pin 
int val1 =0;
int val2 =0;
int val3 =0;
int val4 =0;
void setup() 
{ 
 myservo1.attach(6);  // attaches the servo 1 on pin 6 to the servo object 
 myservo2.attach(9);  // attaches the servo 2 on pin 9 to the servo object 
 myservo2.attach(10);  // attaches the servo 3 on pin 10 to the servo object
 myservo2.attach(11);  // attaches the servo 4 on pin 11 to the servo object
} 
 
void loop() 
{ 
  val1 = analogRead(potpin);            // reads the value of the potentiometer (1) (value between 0 and 1023) 
  val2 = analogRead(potpin1);            // reads the value of the potentiometer (2) (value between 0 and 1023) 
  val3 = analogRead(potpin1);            // reads the value of the potentiometer (3) (value between 0 and 1023) 
  val4 = analogRead(potpin1);            // reads the value of the potentiometer (4) (value between 0 and 1023) 
  val1 = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  val2 = map(val1, 0, 1023, 90, 179);     // scale it to use it with the servo (value between 0 and 180) 
   myservo1.write(val1);                  // pwm 13 sets the servo position according to the scaled value 
   myservo2.write(val2);                  // sets the servo position according to the scaled value 
   myservo3.write(val3);
   myservo4.write(val4);
  delay(15);                           // waits for the servo to get there 
}
