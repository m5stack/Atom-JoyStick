#include "ATOM_FLY_REMOTER.h"

void ATOM_FLY_REMOTER::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                  uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void ATOM_FLY_REMOTER::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                 uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool ATOM_FLY_REMOTER::begin(TwoWire *wire, uint8_t addr, uint8_t sda,
                             uint8_t scl, uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

uint16_t ATOM_FLY_REMOTER::getJoy1ADCValueX(
    atom_fly_remoter_adc_mode_t adc_bits) {
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

uint16_t ATOM_FLY_REMOTER::getJoy1ADCValueY(
    atom_fly_remoter_adc_mode_t adc_bits) {
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

uint16_t ATOM_FLY_REMOTER::getJoy2ADCValueX(
    atom_fly_remoter_adc_mode_t adc_bits) {
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

uint16_t ATOM_FLY_REMOTER::getJoy2ADCValueY(
    atom_fly_remoter_adc_mode_t adc_bits) {
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

uint16_t ATOM_FLY_REMOTER::getBatteryADCValue(
    atom_fly_remoter_adc_mode_t adc_bits) {
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

float ATOM_FLY_REMOTER::getBatteryVoltage(void) {
    uint8_t data[4];
    int32_t value;

    readBytes(_addr, BATTERY_VOLTAGE_REG, data, 2);
    value = data[0] | (data[1] << 8);

    return ((float)value / 100.0f);
}

uint8_t ATOM_FLY_REMOTER::getButtonValue(button_t index) {
    uint8_t data[4];

    uint8_t reg = BUTTON_REG + index;
    readBytes(_addr, reg, data, 1);

    return data[0];
}

void ATOM_FLY_REMOTER::setSystemReset(void) {
    _wire->beginTransmission(_addr);
    _wire->write(0xFC);
    _wire->write(1);
    _wire->endTransmission();
}

uint8_t ATOM_FLY_REMOTER::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();
    _addr = addr;
    return _addr;
}

uint8_t ATOM_FLY_REMOTER::getI2CAddress(void) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t ATOM_FLY_REMOTER::getFirmwareVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

void ATOM_FLY_REMOTER::jumpBootloader(void) {
    uint8_t value = 1;

    writeBytes(_addr, JUMP_TO_BOOTLOADER_REG, (uint8_t *)&value, 1);
}
