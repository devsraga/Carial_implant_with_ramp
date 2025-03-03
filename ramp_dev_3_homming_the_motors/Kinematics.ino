// Define link lengths (adjust based on your robot)
const float L1 = 100.0; // Length of first link
const float L2 = 100.0; // Length of second link
const float L3 = 50.0;  // Length of third link

// Stepper motor parameters with microstepping
const int microstep = 16;  // Microstepping (e.g., 1/16 microstepping)
const float stepsPerRevolution = 200.0 * microstep; // Adjusted for microstepping
const float degreesPerStep = 360.0 / stepsPerRevolution; // New step resolution



// Function to convert step counts to angles (degrees)
float stepsToDegrees(long steps) {
    return steps * degreesPerStep;
}



// Convert angles (degrees) to step counts
long degreesToSteps(float degrees) {
    return (long)(degrees / degreesPerStep);
}



// Forward Kinematics function
void forwardKinematics(long theta1_steps, long theta2_steps, long theta3_steps) {
    // Convert steps to angles
    float theta1 = stepsToDegrees(theta1_steps);
    float theta2 = stepsToDegrees(theta2_steps);
    float theta3 = stepsToDegrees(theta3_steps);

    // Convert degrees to radians
    float theta1_rad = theta1 * PI / 180.0;
    float theta2_rad = theta2 * PI / 180.0;
    float theta3_rad = theta3 * PI / 180.0;

    // Compute end-effector position using FK equations
    float X = L1 * cos(theta1_rad) + L2 * cos(theta1_rad + theta2_rad) + L3 * cos(theta1_rad + theta2_rad + theta3_rad);
    float Y = L1 * sin(theta1_rad) + L2 * sin(theta1_rad + theta2_rad) + L3 * sin(theta1_rad + theta2_rad + theta3_rad);
    float Z = 0; // Assuming a planar robot arm

    // Print result
    Serial.print("End-Effector Position: X = ");
    Serial.print(X);
    Serial.print(" Y = ");
    Serial.print(Y);
    Serial.print(" Z = ");
    Serial.println(Z);
}




// Inverse Kinematics function
bool inverseKinematics(float X, float Y, float Z, long &theta1_steps, long &theta2_steps, long &theta3_steps) {
    // Compute theta1 (base joint)
    float theta1 = atan2(Y, X) * 180.0 / PI;

    // Compute shoulder-to-end-effector distance
    float D = sqrt(X * X + Y * Y);
    float C = sqrt(D * D + Z * Z);

    // Compute theta3 (elbow joint)
    float cos_theta3 = (L1 * L1 + L2 * L2 - C * C) / (2 * L1 * L2);
    if (cos_theta3 < -1 || cos_theta3 > 1) return false; // Out of reach
    float theta3 = acos(cos_theta3) * 180.0 / PI;

    // Compute theta2 (shoulder joint)
    float theta2 = atan2(Z, D) * 180.0 / PI + acos((L1 * L1 + C * C - L2 * L2) / (2 * L1 * C)) * 180.0 / PI;

    // Convert angles to steps
    theta1_steps = degreesToSteps(theta1);
    theta2_steps = degreesToSteps(theta2);
    theta3_steps = degreesToSteps(theta3);

    return true; // IK solution found
}



// Move function integrating FK
void moveRobotArm(long theta1_steps, long theta2_steps, long theta3_steps, 
                  float mot_speed, float accel) {
    // Set speeds and accelerations
    stepperX.setMaxSpeed(mot_speed);
    stepperY.setMaxSpeed(mot_speed);
    stepperZ.setMaxSpeed(mot_speed);

    stepperX.setAcceleration(accel);
    stepperY.setAcceleration(accel);
    stepperZ.setAcceleration(accel);

    // Move motors to the given positions
    moveAllMotors(theta1_steps, theta2_steps, theta3_steps, mot_speed, mot_speed, mot_speed, accel, accel, accel);

}


// Move function integrating FK & IK
void moveToPosition(float X, float Y, float Z, float mot_speed, float accel) {
    long theta1_steps, theta2_steps, theta3_steps;
    
    if (inverseKinematics(X, Y, Z, theta1_steps, theta2_steps, theta3_steps)) {
        Serial.println("IK Solution Found. Moving to position...");

        // Set speeds and accelerations
        stepperX.setMaxSpeed(mot_speed);
        stepperY.setMaxSpeed(mot_speed);
        stepperZ.setMaxSpeed(mot_speed);

        stepperX.setAcceleration(accel);
        stepperY.setAcceleration(accel);
        stepperZ.setAcceleration(accel);

        // Move motors to calculated step positions
        moveAllMotors(theta1_steps, theta2_steps, theta3_steps, mot_speed, mot_speed, mot_speed, accel, accel, accel);

        // Compute and display FK
        forwardKinematics(theta1_steps, theta2_steps, theta3_steps);
    } else {
        Serial.println("IK Solution Not Found! Position Out of Reach.");
    }
}
