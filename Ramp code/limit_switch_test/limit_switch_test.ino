#include <AccelStepper.h>
#define Y_LIMIT_PIN        19   // Example pin for X axis limit switch
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(Y_LIMIT_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(digitalRead(Y_LIMIT_PIN));
delay(1000);
}
