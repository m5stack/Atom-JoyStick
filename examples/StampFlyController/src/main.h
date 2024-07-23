/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include <M5AtomS3.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "M5GFX.h"
#include <atoms3joy.h>
#include "buzzer.h"

extern M5GFX display;

#define CHANNEL 1

#define ANGLECONTROL         0
#define RATECONTROL          1
#define ANGLECONTROL_W_LOG   2
#define RATECONTROL_W_LOG    3
#define ALT_CONTROL_MODE     4
#define NOT_ALT_CONTROL_MODE 5
#define RESO10BIT            (4096)

#define INIT_MODE         0
#define AVERAGE_MODE      1
#define FLIGHT_MODE       2
#define PARKING_MODE      3
#define LOG_MODE          4
#define AUTO_LANDING_MODE 5

extern uint8_t StickMode;
extern uint8_t AltMode;
extern uint8_t Mode;
extern esp_now_peer_info_t peerInfo;
extern volatile float fly_bat_voltage;
extern volatile float roll_angle;
extern volatile float pitch_angle;
extern volatile float yaw_angle;
extern volatile float altitude;
extern volatile uint8_t fly_status;
extern volatile uint8_t fly_status_manual;
extern volatile uint8_t auto_up_down_status;
extern volatile uint32_t auto_up_down_status_counter;
extern volatile uint8_t alt_flag;
extern volatile uint8_t fly_mode;
extern volatile uint8_t last_fly_mode;
extern uint8_t senddata[25];
extern volatile int16_t tof_front;
extern volatile uint8_t proactive_flag;
extern volatile uint32_t proactive_flag_counter;
extern volatile uint8_t is_fly_flag;

uint8_t check_control_mode_change(void);
uint8_t check_alt_mode_change(void);

#endif