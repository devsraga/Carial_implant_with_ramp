#include <AccelStepper.h>

// Define stepper motor pins for each motor
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
void setup() {
  // put your setup code here, to run once:
    pinMode(X_STEP_PIN,OUTPUT); 
  pinMode(X_DIR_PIN,OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
    digitalWrite(X_ENABLE_PIN, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(X_DIR_PIN,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 32*800; x++) {
    digitalWrite(X_STEP_PIN,HIGH); 
    delayMicroseconds(700);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(X_STEP_PIN,LOW); 
    delayMicroseconds(700); 
  }
  delay(1000); // One second delay
}
