#include "Arduino.h"
#include "Matsushita_Thermal.h"

// Constructor
Matsushita_Thermal::Matsushita_Thermal(){
  pinMode(PIN_STEPPER_MOTOR_STEP, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_DIR, OUTPUT);

  pinMode(PIN_STEPPER_MOTOR_MS1, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_MS2, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_MS3, OUTPUT);

  pinMode(PIN_STEPPER_MOTOR_SLEEP, OUTPUT);
  //pinMode(PIN_STEPPER_MOTOR_RESET, OUTPUT);

  reset();

  // default direction
  digitalWrite(PIN_STEPPER_MOTOR_DIR, LOW);
}

void Matsushita_Thermal::setHeat(uint8_t temp) {
  // TODO
}

void Matsushita_Thermal::setSpeed(uint8_t time) {
  // TODO
}

void Matsushita_Thermal::setResolution(uint8_t r) {
  if (r == 1) {
    // Full Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS3, LOW);
  } else if (r == 2) {
    // Half Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS3, LOW);
  } else if (r == 4) {
    // Quarter Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS3, LOW);
  } else if (r == 8) {
    // Eighth Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS3, LOW);
  } else if (r == 16) {
    // Sixteenth Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS3, HIGH);
  }
}

void Matsushita_Thermal::feed(uint8_t lines) {
    for (int i = 0; i < stepsPerRevolution; i++)
    {
      // These four lines result in 1 step:
      digitalWrite(PIN_STEPPER_MOTOR_STEP, HIGH);
      delayMicroseconds(600);
      digitalWrite(PIN_STEPPER_MOTOR_STEP, LOW);
      delayMicroseconds(600);
    }
}

void Matsushita_Thermal::reset() {
  digitalWrite(PIN_STEPPER_MOTOR_RESET, HIGH);
  delayMicroseconds(100);
  digitalWrite(PIN_STEPPER_MOTOR_RESET, LOW);
  delayMicroseconds(100);
}

void Matsushita_Thermal::printLine(int w, uint8_t line) {
  // TODO
}

void Matsushita_Thermal::printBitmap(int w, int h, const uint8_t *bitmap,) {
  // TODO
  // call printLine()
}

void Matsushita_Thermal::printCh(const char c) {
  // TODO
}

void Matsushita_Thermal::printString(const char s) {
  // TODO
  // call printCh()
}

void Matsushita_Thermal::reverseMotor() {
  digitalWrite(PIN_STEPPER_MOTOR_DIR, HIGH);
}

void Matsushita_Thermal::wakeMotor() {
  digitalWrite(PIN_STEPPER_MOTOR_SLEEP, HIGH);
  delay(1);
}

void Matsushita_Thermal::sleepMotor() {
  digitalWrite(PIN_STEPPER_MOTOR_SLEEP, LOW);
}


uint8_t Matsushita_Thermal::readPrintHeadTemperature() {
  // TODO
}

uint16_t Matsushita_Thermal::calculateHeatTime() {
  // TODO
}
