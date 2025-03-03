// Function to home all motors
void homeAllMotors() {
  // Homing sequence for each axis
  homeMotor(stepperX, X_MIN_LIMIT_PIN, -500); // Home X-axis
//  homeMotor(stepperY, Y_MIN_LIMIT_PIN, -500); // Home Y-axis
//  homeMotor(stepperZ, Z_MIN_LIMIT_PIN, -500);  // Home Z-axis

//  
// Set current position as home (0)
  stepperX.setCurrentPosition(0);
//  stepperY.setCurrentPosition(0);
//  stepperZ.setCurrentPosition(0);

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
    delay(500);                           // Small delay to stabilize

  // Move slightly away from the limit switch to ensure it's released
  motor.move(200);   // Move 5 steps away (adjust as needed)
  while (motor.distanceToGo() != 0) {
    motor.run();
  }
  motor.setCurrentPosition(0);         // Set home position to 0
}






// Function to move all motors with different speeds and accelerations, incorporating limit switches
void moveAllMotors(long xPos, long yPos, long zPos,
                   float xSpeed, float ySpeed, float zSpeed, 
                   float xAccel, float yAccel, float zAccel) {
  // Set target positions for each motor
  stepperX.moveTo(xPos);
  stepperY.moveTo(yPos);
  stepperZ.moveTo(zPos);


  // Set speeds and accelerations for each motor
  stepperX.setMaxSpeed(xSpeed);
  stepperY.setMaxSpeed(ySpeed);
  stepperZ.setMaxSpeed(zSpeed);


  stepperX.setAcceleration(xAccel);
  stepperY.setAcceleration(yAccel);
  stepperZ.setAcceleration(zAccel);


  // Continuously update the motor positions until all motors reach their target or a limit switch is triggered
  while (stepperX.isRunning() || stepperY.isRunning() || stepperZ.isRunning()) {
    // Check for limit switches and stop motors if triggered
    if (digitalRead(X_MAX_LIMIT_PIN) == LOW || digitalRead(X_MIN_LIMIT_PIN) == LOW) {  // Assuming LOW when triggered
      stepperX.stop();
      stepperX.runToNewPosition(stepperX.currentPosition() - 10);  // Move back a bit
      return;  // Exit to recompute inverse kinematics
    }

    
    if (digitalRead(Y_MAX_LIMIT_PIN) == LOW || digitalRead(Y_MIN_LIMIT_PIN) == LOW) {
      stepperY.stop();
      stepperY.runToNewPosition(stepperY.currentPosition() - 10);
      return;
    }


    if (digitalRead(Z_MAX_LIMIT_PIN) == LOW || digitalRead(Z_MIN_LIMIT_PIN) == LOW) {
      stepperZ.stop();
      stepperZ.runToNewPosition(stepperZ.currentPosition() - 10);
      return;
    }

    // Run each motor
    stepperX.run();
    stepperY.run();
    stepperZ.run();
  }
}
