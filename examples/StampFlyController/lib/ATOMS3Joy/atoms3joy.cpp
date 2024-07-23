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

uint16_t stick[4];
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
    Wire1.beginTransmission(I2C_ADDRESS);  // I2Cスレーブのデータ送信開始
    Wire1.write(address);                  // x軸指定
    Wire1.endTransmission(false);          // I2Cスレーブのデータ送信終了
    Wire1.requestFrom(I2C_ADDRESS, 2);     // Request 2 bytes from the slave device.
    for (uint8_t i = 0; i < 2; i++) {      // If data is received.
        buffer[i] = Wire1.read();
    }
    data = buffer[1] * 256 + buffer[0];

    return data;
}

uint16_t read_byte_data(uint8_t address) {
    uint16_t data = 0;
    Wire1.beginTransmission(I2C_ADDRESS);  // I2Cスレーブのデータ送信開始
    Wire1.write(address);                  // x軸指定
    Wire1.endTransmission(false);          // I2Cスレーブのデータ送信終了
    Wire1.requestFrom(I2C_ADDRESS, 1);     // Request 1 byte from the slave device.
    data = Wire1.read();
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

void joy_update(void) {
    stick[RIGHTX] = read_2byte_data(RIGHT_STICK_X_ADDRESS);
    stick[RIGHTY] = read_2byte_data(RIGHT_STICK_Y_ADDRESS);
    stick[LEFTX]  = read_2byte_data(LEFT_STICK_X_ADDRESS);
    stick[LEFTY]  = read_2byte_data(LEFT_STICK_Y_ADDRESS);
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