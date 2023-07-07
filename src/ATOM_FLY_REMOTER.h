#ifndef __ATOM_FLY_REMOTER_H
#define __ATOM_FLY_REMOTER_H

#include "Arduino.h"
#include "Wire.h"

#define ATOM_FLY_REMOTER_ADDR     0x59
#define JOY1_ADC_VALUE_12BITS_REG 0x00
#define JOY1_ADC_VALUE_8BITS_REG  0x10
#define JOY2_ADC_VALUE_12BITS_REG 0x20
#define JOY2_ADC_VALUE_8BITS_REG  0x30
#define BATTERY_ADC_12BITS_REG    0x40
#define BATTERY_ADC_8BITS_REG     0x50
#define BATTERY_VOLTAGE_REG       0x60
#define BUTTON_REG                0x70
#define FIRMWARE_VERSION_REG      0xFE
#define I2C_ADDRESS_REG           0xFF
#define JUMP_TO_BOOTLOADER_REG    0xFD

typedef enum { _8bit = 0, _12bit } atom_fly_remoter_adc_mode_t;
typedef enum { BUTTON_1 = 0, BUTTON_2, BUTTON_A, BUTTON_B } button_t;

class ATOM_FLY_REMOTER {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = ATOM_FLY_REMOTER_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000UL);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
    uint8_t getFirmwareVersion(void);
    uint16_t getJoy1ADCValueX(atom_fly_remoter_adc_mode_t adc_bits);
    uint16_t getJoy1ADCValueY(atom_fly_remoter_adc_mode_t adc_bits);
    uint16_t getJoy2ADCValueX(atom_fly_remoter_adc_mode_t adc_bits);
    uint16_t getJoy2ADCValueY(atom_fly_remoter_adc_mode_t adc_bits);
    uint16_t getBatteryADCValue(atom_fly_remoter_adc_mode_t adc_bits);
    uint8_t getButtonValue(button_t index);
    float getBatteryVoltage(void);
    void setSystemReset(void);
    void jumpBootloader(void);
};

#endif
