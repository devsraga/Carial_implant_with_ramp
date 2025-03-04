#include <AccelStepper.h>
#include <math.h>
#include <SPI.h>
#include <SD.h>

// Define stepper motor pins for each motor
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62



// Define limit switch pins for each motor
#define X_MAX_LIMIT_PIN        2   // Example pin for X axis limit switch c5
#define X_MIN_LIMIT_PIN        3  // x

#define Y_MAX_LIMIT_PIN        15   // Example pin for Y axis limit switch c0
#define Y_MIN_LIMIT_PIN        14   //   Y

#define Z_MAX_LIMIT_PIN        19   // Example pin for Z axis limit switch
#define Z_MIN_LIMIT_PIN        18 // Z


const int chipSelect = 10;  // CS pin for the SD card module

// Create AccelStepper objects for each motor
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);






void setup() {
  // Set pin modes for each motor and limit switch
Serial.begin(115200);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);


  pinMode(X_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(X_MIN_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(Y_MIN_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(Z_MIN_LIMIT_PIN, INPUT_PULLUP);



  // Enable motors
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);


  // Set max speed and acceleration for each motor
  stepperX.setMaxSpeed(2000);
  stepperX.setAcceleration(1000);
  
  stepperY.setMaxSpeed(2000);
  stepperY.setAcceleration(1000);
  
  stepperZ.setMaxSpeed(2000);
  stepperZ.setAcceleration(1000);
  
    // Call homing function at startup
  homeAllMotors();
  Serial.println("homming done");
  

    // Initialize SD card and read G-code
//    initializeAndReadGCode();
}

void loop() {
  // Call moveAllMotors to move all motors simultaneously
  // Move to different positions with different speeds and accelerations
  Serial.println("loop entered and waiting for one seconds");
  delay(1000);
  moveAllMotors(1200, 0, -4*3200,   // Target positions for each motor
                600, 0, 600,     // Max speeds for each motor
                600, 0, 600);      // Accelerations for each motor
  
  delay(1000);  // Wait for 1 second before next movement
}
