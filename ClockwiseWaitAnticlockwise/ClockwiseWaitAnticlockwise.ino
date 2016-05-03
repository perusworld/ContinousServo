#include <Servo.h>

#define FORWARD_ANGLE 0
#define REVERSE_ANGLE 180
#define NONE_ANGLE 90
#define PIN 9
#define SLEEPTIME 1000

enum rotation {
  r_forward,
  r_reverse,
  r_none
};

 Servo myservo;
 rotation currentRotation = r_none;
 rotation previousRotation = r_reverse;  
 int maxRotations = 10;
 int maxSleep = 5;
 boolean changeRotation = true;
 int index = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(PIN); 
}

void log(char* msg) {
  Serial.println(msg);
}

void loop() {
  while(true) {
     if (changeRotation) {
      changeRotation = false;
      if (currentRotation == r_none && previousRotation == r_reverse) {
        previousRotation = r_none;
        currentRotation = r_forward;
        myservo.write(FORWARD_ANGLE);
        log("FORWARD_ANGLE");
      } else if (currentRotation == r_forward && previousRotation == r_none) {
        previousRotation = r_forward;
        currentRotation = r_none;
        myservo.write(NONE_ANGLE);
        log("F NONE_ANGLE");
      } else if (currentRotation == r_none && previousRotation == r_forward) {
        previousRotation = r_none;
        currentRotation = r_reverse;
        myservo.write(REVERSE_ANGLE);
        log("REVERSE_ANGLE");
      } else if (currentRotation == r_reverse && previousRotation == r_none) {
        previousRotation = r_reverse;
        currentRotation = r_none;
        myservo.write(NONE_ANGLE);
        log("R NONE_ANGLE");
      }
     }
     delay(SLEEPTIME);
     index++;
     if (currentRotation == r_none) {
       if (index > maxSleep) {
        index = 0;
        log("maxSleep");
        changeRotation = true;
       }
     } else {
       if (index > maxRotations) {
        index = 0;
        log("maxRotations");
        changeRotation = true;
       }
     }
  }
}
