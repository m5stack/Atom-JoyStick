#include "AtomJoyStick.h"

void AtomJoyStick::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void AtomJoyStick::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool AtomJoyStick::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl, uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl);
    _wire->setClock(_speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

uint16_t AtomJoyStick::getJoy1ADCValueX(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = JOY1_ADC_VALUE_12BITS_REG;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = JOY1_ADC_VALUE_8BITS_REG;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

uint16_t AtomJoyStick::getJoy1ADCValueY(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = JOY1_ADC_VALUE_12BITS_REG + 2;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = JOY1_ADC_VALUE_8BITS_REG + 1;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

uint16_t AtomJoyStick::getJoy2ADCValueX(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = JOY2_ADC_VALUE_12BITS_REG;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = JOY2_ADC_VALUE_8BITS_REG;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

uint16_t AtomJoyStick::getJoy2ADCValueY(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = JOY2_ADC_VALUE_12BITS_REG + 2;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = JOY2_ADC_VALUE_8BITS_REG + 1;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

uint16_t AtomJoyStick::getBattery1ADCValue(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = BATTERY_ADC_12BITS_REG;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = BATTERY_ADC_8BITS_REG;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

float AtomJoyStick::getBattery1Voltage(void) {
    uint8_t data[4];
    int32_t value;

    readBytes(_addr, BATTERY_VOLTAGE_REG + 2, data, 2);
    value = data[0] | (data[1] << 8);

    return ((float)value / 1000.0f);
}

uint16_t AtomJoyStick::getBattery2ADCValue(atom_joystick_adc_mode_t adc_bits) {
    uint8_t data[4];
    uint32_t value;

    if (adc_bits == _12bit) {
        uint8_t reg = BATTERY_ADC_12BITS_REG + 2;
        readBytes(_addr, reg, data, 2);
        value = data[0] | (data[1] << 8);
    } else if (adc_bits == _8bit) {
        uint8_t reg = BATTERY_ADC_8BITS_REG + 1;
        readBytes(_addr, reg, data, 1);
        value = data[0];
    }

    return value;
}

float AtomJoyStick::getBattery2Voltage(void) {
    uint8_t data[4];
    int32_t value;

    readBytes(_addr, BATTERY_VOLTAGE_REG, data, 2);
    value = data[0] | (data[1] << 8);

    return ((float)value / 1000.0f);
}

uint8_t AtomJoyStick::getButtonValue(button_t index) {
    uint8_t data[4];

    uint8_t reg = BUTTON_REG + index;
    readBytes(_addr, reg, data, 1);

    return data[0];
}

uint8_t AtomJoyStick::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();
    _addr = addr;
    return _addr;
}

uint8_t AtomJoyStick::getI2CAddress(void) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t AtomJoyStick::getFirmwareVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t AtomJoyStick::getBootloaderVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(BOOTLOADER_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}
