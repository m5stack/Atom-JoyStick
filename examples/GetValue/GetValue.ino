/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "AtomJoyStick.h"

AtomJoyStick joystick;

void setup() {
    USBSerial.begin(115200);

    while (!joystick.begin(&Wire, ATOM_JOYSTICK_ADDR, 38, 39, 400000U)) {
        USBSerial.println("Couldn't find Atom JoyStick");
        delay(2000);
    }

    USBSerial.printf("Atom JoyStick firmware version:%d\n", joystick.getFirmwareVersion());
    USBSerial.printf("Atom JoyStick bootloader version:%d\n", joystick.getBootloaderVersion());
}

void loop() {
    USBSerial.printf("Atom JoyStick Joy1 X:%d\n", joystick.getJoy1ADCValueX(_12bit));
    USBSerial.printf("Atom JoyStick Joy1 Y:%d\n", joystick.getJoy1ADCValueY(_12bit));
    USBSerial.printf("Atom JoyStick Joy2 X:%d\n", joystick.getJoy2ADCValueX(_12bit));
    USBSerial.printf("Atom JoyStick Joy2 Y:%d\n", joystick.getJoy2ADCValueY(_12bit));
    USBSerial.printf("Atom JoyStick Battery1 ADC:%d\n", joystick.getBattery1ADCValue(_12bit));
    USBSerial.printf("Atom JoyStick Battery1 Voltage:%.2fV\n", joystick.getBattery1Voltage());
    USBSerial.printf("Atom JoyStick Battery2 ADC:%d\n", joystick.getBattery2ADCValue(_12bit));
    USBSerial.printf("Atom JoyStick Battery2 Voltage:%.2fV\n", joystick.getBattery2Voltage());
    delay(10);
}