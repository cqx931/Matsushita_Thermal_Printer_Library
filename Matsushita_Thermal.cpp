#include "Arduino.h"
#include "Matsushita_Thermal.h"

// Constructor
Matsushita_Thermal::Matsushita_Thermal(){
  // pins
  pinMode(PIN_STEPPER_MOTOR_STEP, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_DIR, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_ENABLE, OUTPUT);

  pinMode(PIN_STEPPER_MOTOR_MS1, OUTPUT);
  pinMode(PIN_STEPPER_MOTOR_MS2, OUTPUT);

  pinMode(PIN_PRINTHEAD_RANK1, INPUT_PULLUP);
  pinMode(PIN_PRINTHEAD_RANK2, INPUT_PULLUP);

  pinMode(PIN_PRINTHEAD_MOSFET, OUTPUT);
}

void Matsushita_Thermal::init() {
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
  if (r == 2) {
    // Half Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, HIGH);
  } else if (r == 4) {
    // Quarter Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, LOW);
  } else if (r == 8) {
    // Eighth Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, LOW);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, LOW);

  } else if (r == 16) {
    // Sixteenth Step
    digitalWrite(PIN_STEPPER_MOTOR_MS1, HIGH);
    digitalWrite(PIN_STEPPER_MOTOR_MS2, HIGH);
  }
}

void Matsushita_Thermal::feed(uint8_t lines) {
    for (int i = 0; i < STEPS_PER_REVOLUTION; i++)
    {
      // These four lines result in 1 step:
      digitalWrite(PIN_STEPPER_MOTOR_STEP, HIGH);
      delayMicroseconds(500);
      digitalWrite(PIN_STEPPER_MOTOR_STEP, LOW);
      delayMicroseconds(500);
    }
}

void Matsushita_Thermal::printLine(int w, uint8_t line) {
  // TODO
}

void Matsushita_Thermal::printBitmap(int w, int h, const uint8_t *bitmap) {
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

void Matsushita_Thermal::reverse() {
  digitalWrite(PIN_STEPPER_MOTOR_DIR, HIGH);
}

void Matsushita_Thermal::wake() {
  // power on stepper motor
  digitalWrite(PIN_STEPPER_MOTOR_ENABLE, LOW);
  // power on print head
  digitalWrite(PIN_PRINTHEAD_MOSFET, HIGH);
  delay(1);
}

void Matsushita_Thermal::sleep() {
  // power off stepper motor
  digitalWrite(PIN_STEPPER_MOTOR_ENABLE, HIGH);
  // power off print head
  digitalWrite(PIN_PRINTHEAD_MOSFET, LOW);
}

uint8_t Matsushita_Thermal::readHeadResistance() {
  uint8_t v1 = digitalRead(PIN_PRINTHEAD_RANK1);
  uint8_t v2 = digitalRead(PIN_PRINTHEAD_RANK2);

  uint8_t state = v2 | (v1<<1);

  switch (state) {
    case 0:
    return 190;
    break;
    case 1:
    return 177;
    break;
    case 2:
    return 164;
    break;
    case 3:
    return 150;
    break;
    default:
    break;
  }

  return 0;
}

float Matsushita_Thermal::readSupplyVoltage() {
  // reading from a voltage devider: 2 10k resistors
  uint16_t sensorValue = analogRead(PIN_SUPPLY_VOLTAGE);

  float readingVoltage = (float(sensorValue)/1023.0) * 5;
  float supplyVoltage = readingVoltage * 2;
  return supplyVoltage;
}

uint8_t Matsushita_Thermal::readPrintHeadTemperature() {
  // do not operate at 70 C or higher
  uint16_t sensorValue = analogRead(PIN_PRINTHEAD_THERMO);
  sensorValue = 1023 - sensorValue;
  // r1 is 33k
  float rx = (1023.0/float(sensorValue)-1.0)*33000.0;
  float temperature = calculatePrintHeadTemp(uint16_t(rx));
  return uint8_t(temperature);
}

float Matsushita_Thermal::calculatePrintHeadTemp(uint16_t rx) {
  // To solve the function: https://www.symbolab.com/solver/equation-calculator/
  float ln = log(float(rx)/30000.0);
  float temp = -(40677.0*ln-49375.0)/(1975.0+149.0*ln);
  return temp;
}


uint16_t Matsushita_Thermal::calculateHeatTime() {
  // TODO
}
