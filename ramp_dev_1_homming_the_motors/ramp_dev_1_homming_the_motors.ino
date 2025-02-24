#include <AccelStepper.h>

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

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

// Define limit switch pins for each motor
#define X_MAX_LIMIT_PIN        2   // Example pin for X axis limit switch c5
#define X_MIN_LIMIT_PIN        3  // x

#define Y_MAX_LIMIT_PIN        15   // Example pin for Y axis limit switch c0
#define Y_MIN_LIMIT_PIN        14   //   Y

#define Z_MAX_LIMIT_PIN        19   // Example pin for Z axis limit switch
#define Z_MIN_LIMIT_PIN        18 // Z

#define E_LIMIT_PIN        5   // Example pin for E axis limit switch
#define Q_LIMIT_PIN        6   // Example pin for Q axis limit switch

// Create AccelStepper objects for each motor
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper stepperE(AccelStepper::DRIVER, E_STEP_PIN, E_DIR_PIN);
AccelStepper stepperQ(AccelStepper::DRIVER, Q_STEP_PIN, Q_DIR_PIN);


// Function to home all motors
void homeAllMotors() {
  // Homing sequence for each axis
  homeMotor(stepperX, X_MIN_LIMIT_PIN, -500); // Home X-axis
  homeMotor(stepperY, Y_MIN_LIMIT_PIN, -500); // Home Y-axis
  homeMotor(stepperZ, Z_MIN_LIMIT_PIN, -500);  // Home Z-axis
  homeMotor(stepperE, E_LIMIT_PIN, -500);      // Home E-axis
  homeMotor(stepperQ, Q_LIMIT_PIN, -500);      // Home Q-axis
  
  // Set current position as home (0)
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperZ.setCurrentPosition(0);
  stepperE.setCurrentPosition(0);
  stepperQ.setCurrentPosition(0);
}

// Function to home a single motor
void homeMotor(AccelStepper &motor, int limitSwitchPin, float homingSpeed) {
  motor.setMaxSpeed(abs(homingSpeed)); // Set speed for homing
  motor.setAcceleration(500);          // Set a reasonable acceleration
  motor.move(homingSpeed * 1000);      // Move towards home (negative direction)

  // Move motor until limit switch is triggered
  while (digitalRead(limitSwitchPin) != LOW) {
    motor.run();
  }
  
  motor.stop();                        // Stop motor once switch is triggered
  motor.setCurrentPosition(0);         // Set home position to 0
}


// Function to move all motors with different speeds and accelerations, incorporating limit switches
void moveAllMotors(long xPos, long yPos, long zPos, long ePos, long qPos, 
                   float xSpeed, float ySpeed, float zSpeed, float eSpeed, float qSpeed, 
                   float xAccel, float yAccel, float zAccel, float eAccel, float qAccel) {
  // Set target positions for each motor
  stepperX.moveTo(xPos);
  stepperY.moveTo(yPos);
  stepperZ.moveTo(zPos);
  stepperE.moveTo(ePos);
  stepperQ.moveTo(qPos);

  // Set speeds and accelerations for each motor
  stepperX.setMaxSpeed(xSpeed);
  stepperY.setMaxSpeed(ySpeed);
  stepperZ.setMaxSpeed(zSpeed);
  stepperE.setMaxSpeed(eSpeed);
  stepperQ.setMaxSpeed(qSpeed);

  stepperX.setAcceleration(xAccel);
  stepperY.setAcceleration(yAccel);
  stepperZ.setAcceleration(zAccel);
  stepperE.setAcceleration(eAccel);
  stepperQ.setAcceleration(qAccel);

  // Continuously update the motor positions until all motors reach their target or a limit switch is triggered
  while (stepperX.isRunning() || stepperY.isRunning() || stepperZ.isRunning() || stepperE.isRunning() || stepperQ.isRunning()) {
    // Check for limit switches and stop motors if triggered
    if (digitalRead(X_MAX_LIMIT_PIN) == LOW) {  // Assuming LOW when triggered
      stepperX.stop();
    }
    if (digitalRead(X_MIN_LIMIT_PIN) == LOW) {  // Assuming LOW when triggered
      stepperX.stop();
    }
    
    if (digitalRead(Y_MAX_LIMIT_PIN) == LOW) {
      stepperY.stop();
    }

    if (digitalRead(Y_MIN_LIMIT_PIN) == LOW) {
      stepperY.stop();
    }
    if (digitalRead(Z_MAX_LIMIT_PIN) == LOW) {
      stepperZ.stop();
    }

    if (digitalRead(Z_MIN_LIMIT_PIN) == LOW) {
      stepperZ.stop();
    }
    if (digitalRead(E_LIMIT_PIN) == LOW) {
      stepperE.stop();
    }
    if (digitalRead(Q_LIMIT_PIN) == LOW) {
      stepperQ.stop();
    }

    // Run each motor
    stepperX.run();
    stepperY.run();
    stepperZ.run();
    stepperE.run();
    stepperQ.run();
  }
}





void setup() {
  // Set pin modes for each motor and limit switch

  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(E_ENABLE_PIN, OUTPUT);
  pinMode(Q_ENABLE_PIN, OUTPUT);

  pinMode(X_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(X_MIN_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(Y_MIN_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_LIMIT_PIN, INPUT_PULLUP);  // Assuming active LOW limit switches
  pinMode(Z_MIN_LIMIT_PIN, INPUT_PULLUP);

  pinMode(E_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Q_LIMIT_PIN, INPUT_PULLUP);

  // Enable motors
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E_ENABLE_PIN, LOW);
  digitalWrite(Q_ENABLE_PIN, LOW);

  // Set max speed and acceleration for each motor
  stepperX.setMaxSpeed(2000);
  stepperX.setAcceleration(1000);
  
  stepperY.setMaxSpeed(2000);
  stepperY.setAcceleration(1000);
  
  stepperZ.setMaxSpeed(2000);
  stepperZ.setAcceleration(1000);
  
  stepperE.setMaxSpeed(2000);
  stepperE.setAcceleration(1000);
  
  stepperQ.setMaxSpeed(2000);
  stepperQ.setAcceleration(1000);

    // Call homing function at startup
  homeAllMotors();
}

void loop() {
  // Call moveAllMotors to move all motors simultaneously
  // Move to different positions with different speeds and accelerations
  moveAllMotors(8*3200, 0, -4*3200, 0, 3000,   // Target positions for each motor
                500, 0, 600, 1400, 1200,     // Max speeds for each motor
                500, 0, 600, 200, 230);      // Accelerations for each motor
  
  delay(1000);  // Wait for 1 second before next movement
}
