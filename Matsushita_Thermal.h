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
#define PIN_STEPPER_MOTOR_DIR 2
#define PIN_STEPPER_MOTOR_STEP 3
#define PIN_STEPPER_MOTOR_ENABLE 4

// TMP: PORT A is reserved to the motor, output
// how to better define it through port?
#define PIN_STEPPER_MOTOR_MS1 5 // Logic
#define PIN_STEPPER_MOTOR_MS2 6 // Logic

#define PIN_PRINTHEAD_RANK1 7 // Read
#define PIN_PRINTHEAD_RANK2 8 // Read
#define PIN_PRINTHEAD_MOSFET 9 // Vpp Switch

#define PIN_PRINTHEAD_THERMO A0 // Read: Thermistor
#define PIN_SUPPLY_VOLTAGE A1 // Read: Supply Voltage
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

    void init(),
    setHeat(uint8_t temp),
    setSpeed(uint8_t time),
    reverse(),
    feed(uint8_t lines),
    wake(), sleep(),
    setResolution(uint8_t r),
    printString(const char s),
    printBitmap(int w, int h, const uint8_t *bitmap);
    // these go to private later
    float readSupplyVoltage();
    uint8_t readHeadResistance();
    uint8_t readPrintHeadTemperature();

  private:
    void
    printLine(int w, uint8_t line), printCh(const char c);
    float calculatePrintHeadTemp(uint16_t rx);
    uint16_t calculateHeatTime();
};

#endif // MATSUSHITA_THERMAL_H
