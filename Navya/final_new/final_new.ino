#include <AccelStepper.h>

AccelStepper xMotor(1, 5, 6); // X-axis motor: pin 5 (step), pin 6 (direction)
AccelStepper yMotor(1, 2, 3); // Y-axis motor: pin 2 (step), pin 3 (direction)

// Configuration
const float stepsPerMM = 200.0; // Steps per mm (adjusted for pulley system)
const float xfeedRate = 30;     // Feed rate in mm/min
const float yfeedRate = 0.5;     // Feed rate in mm/min
const float xstepsPerSecond = (xfeedRate * stepsPerMM) / 60.0; // Steps/sec
const float ystepsPerSecond = (yfeedRate * stepsPerMM) / 60.0; // Steps/sec
const float x_axis;
const float y_axis;

const float x_cal_factor;
const float y_cal_factor;

const float x_axis_data[];
const float y_axis_data[];
int data_size = sizeof(x_axis_data) / sizeof(x_axis_data[0]);


void setup() {
  Serial.begin(9600);

  // Configure motors
  xMotor.setMaxSpeed(xstepsPerSecond);
  yMotor.setMaxSpeed(ystepsPerSecond);
  xMotor.setAcceleration(xstepsPerSecond); // Smooth start
  yMotor.setAcceleration(ystepsPerSecond); // Smooth start

  Serial.println("Moving 1 cm into the workpiece...");
  moveMotor(xMotor, 10 * stepsPerMM); // Move X-axis
  Serial.println("Finished moving into the workpiece.");

  Serial.println("Starting square motion...");
//  performSquareMotion();
motion(x_axis_data, y_axis_data);
  Serial.println("Finished square motion.");

  while (true) {} // Halt further execution
}

void loop() {
  // Empty as motion is performed only in setup()
}

void performSquareMotion() {
  float xsquareSide = 6.0; // Side of the square in mm
  float ysquareSide = 12.0;
  float xdistanceInSteps = xsquareSide * stepsPerMM;
  float ydistanceInSteps = ysquareSide * stepsPerMM; 

  Serial.println("Moving Y backward...");
  moveMotor(yMotor, -ydistanceInSteps);

  Serial.println("Moving X backward...");
  moveMotor(xMotor, -xdistanceInSteps);

  Serial.println("Moving Y forward...");
  moveMotor(yMotor, xdistanceInSteps);
}

void moveMotor(AccelStepper& motor, float distance) {
  motor.move(distance);
  while (motor.distanceToGo() != 0) {
    motor.run();
  }
}

void moveMotors(AccelStepper& motorX, float distanceX, AccelStepper& motorY, float distanceY) {
  motorX.move(distanceX);
  motorY.move(distanceY);

  // Run both motors until they reach their target
  while (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0) {
    motorX.run();
    motorY.run();
  }
}

void mov(float x_axis, float y_axis) {
moveMotors(motorX, x_axis * stepsPerMM, motorY, y_axis * stepsPerMM)
}


void mov_x(float x_axis) {
  moveMotor(xMotor, x_axis * stepsPerMM); // Move X-axis
}

void mov_y(float y_axis) {
  moveMotor(yMotor, y_axis * stepsPerMM); // Move Y-axis
}

float calibration_x(float x_axis) {
  x_axis = x_cal_factor * x_axis
  return x-axis;
}

float calibration_y(float y_axis) {
  y_axis = y_cal_factor * y_axis
  return y_axis;
}

void motion(x_axis_data, y_axis_data){
  for (i = 0; i<= data_size; i++){
    mov(x_axis[i], y_axis[i]);
  }
}
