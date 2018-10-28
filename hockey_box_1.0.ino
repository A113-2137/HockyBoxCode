#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo1;  // create servo object to control a servo 
 
int potpin = 0;  // pot in is 13 pwm analog pin used to connect the potentiometer
int potpin1 = 1;  // analog pin used to connect the potentiometerint val;    // variable to read the value from the analog pin 
int val =0;
int val1=0;
void setup() 
{ 
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
 myservo1.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) //
  val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  val1 = map(val1, 0, 1023, 90, 179);     // scale it to use it with the servo (value between 0 and 180) 
   myservo.write(val);                  // pwm 13 sets the servo position according to the scaled value 
   myservo1.write(val1);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}
