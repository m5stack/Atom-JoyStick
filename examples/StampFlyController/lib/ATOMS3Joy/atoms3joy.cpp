/*
 * MIT License
 *
 * Copyright (c) 2024 Kouhei Ito
 * Copyright (c) 2024 M5Stack Technology CO LTD
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <atoms3joy.h>
#include <Wire.h>

#define STICK_CENTER_VALUE (2048)
#define STICK_READ_HOLD_MS (100)

uint16_t stick[4] = {STICK_CENTER_VALUE, STICK_CENTER_VALUE, STICK_CENTER_VALUE, STICK_CENTER_VALUE};
static uint32_t stick_last_ok_ms = 0;
uint8_t button[4];
int16_t button_counter[4];
uint8_t button_state[4]     = {0};
uint8_t button_old_state[4] = {0};
uint8_t buffer[4];
float Battery_voltage[2];
uint8_t THROTTLE      = RIGHTY;
uint8_t AILERON       = LEFTX;
uint8_t ELEVATOR      = LEFTY;
uint8_t RUDDER        = RIGHTX;
uint8_t ARM_BUTTON    = RIGHT_STICK_BUTTON;
uint8_t MODE_BUTTON   = RIGHT_BUTTON;
uint8_t FLIP_BUTTON   = LEFT_STICK_BUTTON;
uint8_t OPTION_BUTTON = LEFT_BUTTON;

uint16_t read_2byte_data(uint8_t address) {
    uint16_t data = 0;
    Wire.beginTransmission(I2C_ADDRESS);  // I2Cスレーブのデータ送信開始
    Wire.write(address);                  // x軸指定
    Wire.endTransmission(false);          // I2Cスレーブのデータ送信終了
    Wire.requestFrom(I2C_ADDRESS, 2);     // Request 2 bytes from the slave device.
    for (uint8_t i = 0; i < 2; i++) {      // If data is received.
        buffer[i] = Wire.read();
    }
    data = buffer[1] * 256 + buffer[0];

    return data;
}

uint16_t read_byte_data(uint8_t address) {
    uint16_t data = 0;
    Wire.beginTransmission(I2C_ADDRESS);  // I2Cスレーブのデータ送信開始
    Wire.write(address);                  // x軸指定
    Wire.endTransmission(false);          // I2Cスレーブのデータ送信終了
    Wire.requestFrom(I2C_ADDRESS, 1);     // Request 1 byte from the slave device.
    data = Wire.read();
    return data;
}

float getBatteryVoltage(uint8_t addr) {
    int32_t value;

    value = read_2byte_data(addr);
#ifdef NEW_ATOM_JOY
    return ((float)value / 1000.0f);
#else
    return ((float)value / 100.0f);
#endif
}

static bool read_stick_data(uint8_t address, uint16_t *value) {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(address);
    Wire.endTransmission(false);
    if (Wire.requestFrom(I2C_ADDRESS, 2) != 2) {
        return false;
    }
    uint8_t low  = Wire.read();
    uint8_t high = Wire.read();
    *value       = high * 256 + low;
    return true;
}

// Keep the last valid values on brief read failures, center the sticks if failures persist.
static void update_sticks(void) {
    uint16_t value[4];
    bool read_ok = read_stick_data(RIGHT_STICK_X_ADDRESS, &value[RIGHTX]) &&
                   read_stick_data(RIGHT_STICK_Y_ADDRESS, &value[RIGHTY]) &&
                   read_stick_data(LEFT_STICK_X_ADDRESS, &value[LEFTX]) &&
                   read_stick_data(LEFT_STICK_Y_ADDRESS, &value[LEFTY]);
    uint32_t now_ms = millis();

    if (read_ok) {
        memcpy(stick, value, sizeof(stick));
        stick_last_ok_ms = now_ms;
    } else if (now_ms - stick_last_ok_ms >= STICK_READ_HOLD_MS) {
        for (uint8_t i = 0; i < 4; i++) {
            stick[i] = STICK_CENTER_VALUE;
        }
    }
}

void joy_update(void) {
    update_sticks();
    for (uint8_t i = 0; i < 4; i++) {
        button_old_state[i] = button_state[i];
        // ボタンの読み込み
        button[i] = (~read_byte_data(LEFT_STICK_BUTTON_ADDRESS + i)) & 0x01;
        // ボタンの処理
        if (button[i] == 1) {
            if (button_counter[i] < 0) button_counter[i] = 0;
            button_counter[i]++;
            if (button_counter[i] > 10) {
                button_counter[i] = 10;
                button_state[i]   = 1;  // 押し確定
            }
        } else {
            if (button_counter[i] > 0) button_counter[i] = 0;
            button_counter[i]--;
            if (button_counter[i] < -10) {
                button_counter[i] = -10;
                button_state[i]   = 0;  // 放し確定
            }
        }
    }

    Battery_voltage[0] = getBatteryVoltage(BATTERY_VOLTAGE1);
#ifdef NEW_ATOM_JOY
    Battery_voltage[1] = getBatteryVoltage(BATTERY_VOLTAGE2);
#endif
#if 0
    USBSerial.printf("%4d %4d %4d %4d %3d %3d %3d %3d\n\r", 
                                            stick[RIGHTX],
                                            stick[RIGHTY],
                                            stick[LEFTX],
                                            stick[LEFTY],
                                            button[RIGHT_STICK_BUTTON],
                                            button[LEFT_STICK_BUTTON],
                                            button[RIGHT_BUTTON],
                                            button[LEFT_BUTTON]);
#endif
}

uint16_t getThrottle(void) {
    return stick[THROTTLE];
}
uint16_t getAileron(void) {
    return stick[AILERON];
}
uint16_t getElevator(void) {
    return stick[ELEVATOR];
}
uint16_t getRudder(void) {
    return stick[RUDDER];
}
uint8_t getArmButton(void) {
    return button[ARM_BUTTON];
}
uint8_t getModeButton(void) {
    return button[MODE_BUTTON];
}
uint8_t getFlipButton(void) {
    return button[FLIP_BUTTON];
}
uint8_t getOptionButton(void) {
    return button[OPTION_BUTTON];
}