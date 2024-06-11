// C++ code
//
#include <Servo.h>
int trigPin = 7;    // Trigger
int echoPin = 6;    // Echo
float duration, cm;
Servo servo_2; //Definition of the servo


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup()
{
  pinMode(trigPin, OUTPUT); //Sets the pinmodes for the sensor
  pinMode(echoPin, INPUT);
  
  pinMode(A0, INPUT); //Set the read for the altimeter
  
  Serial.begin(9600);
  
  servo_2.attach(2, 500, 2500); //Define the servo pin and the max and min
}

void loop()
{
  Serial.println(analogRead(A0));
  // The ultrasonic sensor is a back up for the altimeter.
 // If the altimeter and the ultrasonic read more than certain altitude, the airbrakes activate
  if ((analogRead(A0) >= 300) && (0.01723 * readUltrasonicDistance(7, 6)) > 200) {
    servo_2.write(180);
  } 
  //If the conditions doesnt fit, the airbrakes doesnt activate
  else {
    servo_2.write(0);
  }
  delay(10); // Delay a little bit to improve simulation performance
}