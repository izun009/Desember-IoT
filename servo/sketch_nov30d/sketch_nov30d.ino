// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 11; 
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Serial.begin(9600);
}
int val;
void loop(){ 

  val = random(100); 
  tone(11,val);
  Serial.println(val);
    delay(100);
  }
  
