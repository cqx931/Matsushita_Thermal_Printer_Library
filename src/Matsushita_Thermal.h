/*

  Matsushita_Thermal
  An arduino library written to control the printhead MATSUSHITA EPL1801S2E.
  Created by Qianxun Chen, 2022.
  MIT License

*/

#ifndef MATSUSHITA_THERMAL_H
#define MATSUSHITA_THERMAL_H

#include "Arduino.h"

// Define steps per line

// TMP: TEST
#define PIN_STEPPER_MOTOR_STEP 2
#define PIN_STEPPER_MOTOR_DIR 3
#define PIN_STEPPER_MOTOR_SLEEP 4
#define PIN_STEPPER_MOTOR_RESET 5

// TMP: PORT A is reserved to the motor, output
// how to better define it through port?
// #define PIN_STEPPER_MOTOR_STEP 22
// #define PIN_STEPPER_MOTOR_DIR 23  // Direction of the motor, if you just want rotation in a single direction, you can tie DIR directly to VCC or GND.
// #define PIN_STEPPER_MOTOR_SLEEP 24
// #define PIN_STEPPER_MOTOR_RESET 25
// #define PIN_STEPPER_MOTOR_MS1 26 // Logic
// #define PIN_STEPPER_MOTOR_MS2 27 // Logic
// #define PIN_STEPPER_MOTOR_MS3 28 // Logic

#define STEPS_PER_REVOLUTION 100

// TODO: ports
// Reference: https://elektro.turanis.de/html/prj129/index.html
// Ports on Arduino Mega:  https://github.com/arduino/ArduinoCore-avr/blob/master/variants/mega/pins_arduino.h
// Digital Ports:
// PA 0-7 : D22-29
// PB 4-7 : D10-13 PWM
// PC 0-7 : D37-D30
// PE 3,4,5 : D5, D2, D3 PWM
// PG 5 : D4 PWM
// PH 4-6 : D7-9 PWM
// PL 0-7 D49-D42

// Analog Ports:
// PF 0-7 : A0-7
// PK 0-7 : A8-15

class Matsushita_Thermal {

  public:
    Matsushita_Thermal();
    setHeat();
    setSpeed();

    feed();

    printCh();
    printString();
    printBitmap();
    printLine();

  private:
    void wakeMotor(), sleepMotor();
    uint8_t readPrintHeadTemperature();
    uint16_t calculateHeatTime();
};

#endif // MATSUSHITA_THERMAL_H
