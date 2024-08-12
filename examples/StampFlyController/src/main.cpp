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

// Controller for M5Fly
// #define DEBUG

#include "main.h"
#include <FS.h>
#include <SPIFFS.h>
#include "lvgl_porting.h"

#include "./images/pair_confirm.h"
#include "./images/press_fly.h"
#include "./images/pair_success.h"
#include "./images/move_start_0.h"
#include "./images/move_start_1.h"
#include "./images/move_start_2.h"
#include "./images/move_start_3.h"
#include "./images/move_start_4.h"
#include "./images/move_start_5.h"

#include "app_lvgl.h"

M5GFX display;

TaskHandle_t task_tone_handle = NULL;
esp_now_peer_info_t peerInfo;

float Throttle;
float Phi, Theta, Psi;
uint16_t Phi_bias          = 2048;
uint16_t Theta_bias        = 2048;
uint16_t Psi_bias          = 2048;
uint16_t Throttle_bias     = 2048;
short xstick               = 0;
short ystick               = 0;
uint8_t Mode               = ANGLECONTROL;
uint8_t AltMode            = ALT_CONTROL_MODE;
volatile uint8_t Loop_flag = 0;
float Timer                = 0.0;
float dTime                = 0.01;
uint8_t Timer_state        = 0;
uint8_t StickMode          = 2;
uint32_t espnow_version;

unsigned long stime, etime, dtime;
byte axp_cnt = 0;

char data[140];
uint8_t senddata[25];  // 19->22->23->24->25
uint8_t disp_counter = 0;

volatile uint8_t is_peering                   = 0;
volatile uint8_t fly_status                   = 0;
volatile uint8_t fly_status_manual            = 0;
volatile uint8_t auto_up_down_status          = 0;
volatile uint32_t auto_up_down_status_counter = 0;

volatile float fly_bat_voltage = 0.0f;
volatile float roll_angle      = 0.0f;
volatile float pitch_angle     = 0.0f;
volatile float yaw_angle       = 0.0f;
volatile float altitude        = 0.0f;
volatile int16_t tof_front     = 0.0;

volatile uint8_t alt_flag      = 0;
volatile uint8_t fly_mode      = 0;
volatile uint8_t last_fly_mode = 0;

volatile uint8_t proactive_flag          = 0;
volatile uint32_t proactive_flag_counter = 0;

// StampFly MAC ADDRESS
// 1 F4:12:FA:66:80:54 (Yellow)
// 2 F4:12:FA:66:77:A4
uint8_t Addr1[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Addr2[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Channel
uint8_t Ch_counter;
volatile uint8_t Received_flag             = 0;
volatile uint8_t Channel                   = CHANNEL;
volatile uint8_t is_fly_flag               = 0;
volatile unsigned long is_fly_flag_counter = 0;

void rc_init(void);
void data_send(void);
void show_battery_info();
void voltage_print(void);
void task_tone(void *pvParameters);

// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *recv_data, int data_len) {
    if (is_peering) {
        if (recv_data[7] == 0xaa && recv_data[8] == 0x55 && recv_data[9] == 0x16 && recv_data[10] == 0x88) {
            Received_flag = 1;
            Channel       = recv_data[0];
            Addr2[0]      = recv_data[1];
            Addr2[1]      = recv_data[2];
            Addr2[2]      = recv_data[3];
            Addr2[3]      = recv_data[4];
            Addr2[4]      = recv_data[5];
            Addr2[5]      = recv_data[6];
            USBSerial.printf("Receive !\n");
        }
    } else {
        if (recv_data[0] == 88 && recv_data[1] == 88) {
            memcpy((uint8_t *)&roll_angle, &recv_data[2 + 4 * (3 - 1)], 4);
            memcpy((uint8_t *)&pitch_angle, &recv_data[2 + 4 * (4 - 1)], 4);
            memcpy((uint8_t *)&yaw_angle, &recv_data[2 + 4 * (5 - 1)], 4);
            memcpy((uint8_t *)&fly_bat_voltage, &recv_data[2 + 4 * (15 - 1)], 4);
            memcpy((uint8_t *)&altitude, &recv_data[2 + 4 * (25 - 1)], 4);
            alt_flag = recv_data[2 + 4 * (28 - 1)];
            fly_mode = recv_data[2 + 4 * (28 - 1) + 1];
            memcpy((uint8_t *)&tof_front, &recv_data[2 + 4 * (28 - 1) + 2], 2);
            is_fly_flag = 1;
            if (fly_mode == PARKING_MODE) {
                fly_status_manual = 0;
            }
            // USBSerial.printf("roll:%.2f, pitch:%.2f, yaw:%.2f, voltage:%.2f, alt_flag:%d, fly_mode:%d,
            // tof_front:%d\r\n", roll_angle, pitch_angle, yaw_angle, fly_bat_voltage, alt_flag, fly_mode, tof_front);
        }
    }
}

#define BUF_SIZE 128
// EEPROMにデータを保存する
void save_data(void) {
    if (!SPIFFS.begin()) {
        // 初始化失败时处理
        USBSerial.println("SPIFFS-An error occurred while mounting SPIFFS");

        // 格式化SPIFFS分区
        if (SPIFFS.format()) {
            // 格式化成功
            USBSerial.println("SPIFFS partition formatted successfully");
            // 重启
            esp_restart();
        } else {
            USBSerial.println("SPIFFS partition format failed");
        }
        esp_restart();
    } else {
        /* CREATE FILE */
        File fp = SPIFFS.open("/peer_info.txt", FILE_WRITE);  // 書き込み、存在すれば上書き
        char buf[BUF_SIZE + 1];
        sprintf(buf, "%d,%02X,%02X,%02X,%02X,%02X,%02X", Channel, Addr2[0], Addr2[1], Addr2[2], Addr2[3], Addr2[4],
                Addr2[5]);
        fp.write((uint8_t *)buf, BUF_SIZE);
        fp.close();
        SPIFFS.end();

        USBSerial.printf("Saved Data:%d,[%02X:%02X:%02X:%02X:%02X:%02X]", Channel, Addr2[0], Addr2[1], Addr2[2],
                         Addr2[3], Addr2[4], Addr2[5]);
    }
}

// EEPROMからデータを読み出す
void load_data(void) {
    SPIFFS.begin(true);
    File fp = SPIFFS.open("/peer_info.txt", FILE_READ);
    char buf[BUF_SIZE + 1];
    while (fp.read((uint8_t *)buf, BUF_SIZE) == BUF_SIZE) {
        // USBSerial.print(buf);
        sscanf(buf, "%hhd,%hhX,%hhX,%hhX,%hhX,%hhX,%hhX", &Channel, &Addr2[0], &Addr2[1], &Addr2[2], &Addr2[3],
               &Addr2[4], &Addr2[5]);
        USBSerial.printf("%d,%02X,%02X,%02X,%02X,%02X,%02X\n\r", Channel, Addr2[0], Addr2[1], Addr2[2], Addr2[3],
                         Addr2[4], Addr2[5]);
    }
    fp.close();
    SPIFFS.end();
}

void rc_init(uint8_t ch, uint8_t *addr) {
    // ESP-NOW初期化
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK) {
        esp_now_unregister_recv_cb();
        esp_now_register_recv_cb(OnDataRecv);
        USBSerial.println("ESPNow Init Success");
    } else {
        USBSerial.println("ESPNow Init Failed");
        ESP.restart();
    }

    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, addr, 6);
    peerInfo.channel = ch;
    peerInfo.encrypt = false;
    uint8_t peer_mac_addre;
    while (esp_now_add_peer(&peerInfo) != ESP_OK) {
        USBSerial.println("Failed to add peer");
    }
    esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
}

void peering(void) {
    uint8_t break_flag;
    uint32_t beep_delay = 0;
    char dis_buff[100]  = {0};
    // StampFlyはMACアドレスをFF:FF:FF:FF:FF:FFとして
    // StampFlyのMACアドレスをでブロードキャストする
    // その際にChannelが機体と送信機で同一でない場合は受け取れない
    //  ESP-NOWコールバック登録
    esp_now_unregister_recv_cb();
    esp_now_register_recv_cb(OnDataRecv);

    // ペアリング
    Ch_counter = 1;
    while (1) {
        USBSerial.printf("Try channel %02d.\n\r", Ch_counter);
        peerInfo.channel = Ch_counter;
        peerInfo.encrypt = false;
        while (esp_now_mod_peer(&peerInfo) != ESP_OK) {
            USBSerial.println("Failed to mod peer");
        }
        esp_wifi_set_channel(Ch_counter, WIFI_SECOND_CHAN_NONE);

        // Wait receive StampFly MAC Address
        // uint32_t counter=1;
        // Channelをひとつづつ試していく
        for (uint8_t i = 0; i < 100; i++) {
            break_flag = 0;
            if (Received_flag == 1) {
                break_flag = 1;
                break;
            }
            usleep(100);
        }
        if (millis() - beep_delay >= 500) {
            beep();
            beep_delay = millis();
        }
        if (break_flag) break;
        Ch_counter++;
        if (Ch_counter == 15) Ch_counter = 1;
    }
    // Channel = Ch_counter;

    save_data();
    is_peering = 0;
    display.startWrite();
    display.pushImage(0, 0, pair_success_Width, pair_success_Height, pair_success_);
    display.endWrite();
    buzzer_sound(4000, 600);
    delay(1000);

    USBSerial.printf("Channel:%02d\n\r", Channel);
    USBSerial.printf("MAC2:%02X:%02X:%02X:%02X:%02X:%02X:\n\r", Addr2[0], Addr2[1], Addr2[2], Addr2[3], Addr2[4],
                     Addr2[5]);
    USBSerial.printf("MAC1:%02X:%02X:%02X:%02X:%02X:%02X:\n\r", Addr1[0], Addr1[1], Addr1[2], Addr1[3], Addr1[4],
                     Addr1[5]);

    // Peering
    while (esp_now_del_peer(Addr1) != ESP_OK) {
        Serial.println("Failed to delete peer1");
    }
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, Addr2, 6);  // Addr1->Addr2 ////////////////////////////
    peerInfo.channel = Channel;
    peerInfo.encrypt = false;
    while (esp_now_add_peer(&peerInfo) != ESP_OK) {
        USBSerial.println("Failed to add peer2");
    }
    esp_wifi_set_channel(Channel, WIFI_SECOND_CHAN_NONE);
    display.startWrite();
    display.clear(BLACK);
    display.endWrite();
    esp_restart();
}

void change_channel(uint8_t ch) {
    peerInfo.channel = ch;
    if (esp_now_mod_peer(&peerInfo) != ESP_OK) {
        USBSerial.println("Failed to modify peer");
        return;
    }
    esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
}

// 周期カウンタ割り込み関数
hw_timer_t *timer = NULL;
void IRAM_ATTR onTimer() {
    Loop_flag = 1;
    // Timer = Timer + dTime;
}

void setup() {
    M5.begin();
    Wire1.begin(38, 39);
    Wire1.setClock(400 * 1000);
    load_data();
    M5.update();
    setup_pwm_buzzer();
    display.begin();
    display.setEpdMode(epd_mode_t::epd_quality);

    if (M5.Btn.isPressed() || (Addr2[0] == 0xFF && Addr2[1] == 0xFF && Addr2[2] == 0xFF && Addr2[3] == 0xFF &&
                               Addr2[4] == 0xFF && Addr2[5] == 0xFF)) {
        display.startWrite();
        display.pushImage(0, 0, pair_confirm_Width, pair_confirm_Height, pair_confirm_);
        display.endWrite();
        while (1) {
            M5.update();
            if (M5.Btn.wasPressed()) {
                is_peering = 1;
                break;
            }
        }
        rc_init(1, Addr1);
        USBSerial.printf("Button pressed!\n\r");
        display.startWrite();
        display.pushImage(0, 0, press_fly_Width, press_fly_Height, press_fly_);
        display.endWrite();
        peering();
    }
#ifdef DEBUG
    else
        rc_init(Channel, Addr1);
#else
    else
        rc_init(Channel, Addr2);
#endif

    xTaskCreatePinnedToCore(task_tone,          // 任务函数
                            "task_tone",        // 任务名称
                            1024 * 2,           // 堆栈大小
                            NULL,               // 传递参数
                            0,                  // 任务优先级
                            &task_tone_handle,  // 任务句柄
                            tskNO_AFFINITY);    // 无关联，不绑定在任何一个核上

    display.startWrite();
    display.pushImage(0, 0, move_start_0_Width, move_start_0_Height, move_start_0_);
    display.endWrite();
    delay(100);
    display.startWrite();
    display.pushImage(0, 0, move_start_1_Width, move_start_1_Height, move_start_1_);
    display.endWrite();
    delay(100);
    display.startWrite();
    display.pushImage(0, 0, move_start_2_Width, move_start_2_Height, move_start_2_);
    display.endWrite();
    delay(100);
    display.startWrite();
    display.pushImage(0, 0, move_start_3_Width, move_start_3_Height, move_start_3_);
    display.endWrite();
    delay(100);
    display.startWrite();
    display.pushImage(0, 0, move_start_4_Width, move_start_4_Height, move_start_4_);
    display.endWrite();
    delay(100);
    display.startWrite();
    display.pushImage(0, 0, move_start_5_Width, move_start_5_Height, move_start_5_);
    display.endWrite();
    delay(1100);

    joy_update();

    StickMode = 2;
    // if(getOptionButton())
    // {
    //   StickMode = 3;
    //   display.startWrite();
    //   display.drawCenterString("Please release button.", display.width()/2, display.height()/2);
    //   display.endWrite();
    //   while(getOptionButton())joy_update();
    // }
    AltMode = ALT_CONTROL_MODE;
    delay(500);

    lvgl_init();

    if (StickMode == 3) {
        THROTTLE      = RIGHTY;
        AILERON       = LEFTX;
        ELEVATOR      = LEFTY;
        RUDDER        = RIGHTX;
        ARM_BUTTON    = RIGHT_STICK_BUTTON;
        FLIP_BUTTON   = LEFT_STICK_BUTTON;
        MODE_BUTTON   = RIGHT_BUTTON;
        OPTION_BUTTON = LEFT_BUTTON;
    } else {
        THROTTLE      = LEFTY;
        AILERON       = RIGHTX;
        ELEVATOR      = RIGHTY;
        RUDDER        = LEFTX;
        ARM_BUTTON    = LEFT_STICK_BUTTON;
        FLIP_BUTTON   = RIGHT_STICK_BUTTON;
        MODE_BUTTON   = RIGHT_BUTTON;
        OPTION_BUTTON = LEFT_BUTTON;
    }

    byte error, address;
    int nDevices;

    ////////////////////////////////////////////////////////
    USBSerial.println("Scanning... Wire1");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire1.beginTransmission(address);
        error = Wire1.endTransmission();

        if (error == 0) {
            USBSerial.print("I2C device found at address 0x");
            if (address < 16) USBSerial.print("0");
            USBSerial.print(address, HEX);
            USBSerial.println("  !");

            nDevices++;
        } else if (error == 4) {
            USBSerial.print("Unknown error at address 0x");
            if (address < 16) USBSerial.print("0");
            USBSerial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        USBSerial.println("No I2C devices found\n");
    else
        USBSerial.println("done\n");

    esp_now_get_version(&espnow_version);
    USBSerial.printf("Version %d\n", espnow_version);

    // 割り込み設定
    timer = timerBegin(1, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    delay(100);
}

uint8_t check_control_mode_change(void) {
    uint8_t state;
    static uint8_t flag = 0;
    state               = 0;
    if (flag == 0) {
        if (getOptionButton() == 1) {
            flag = 1;
        }
    } else {
        if (getOptionButton() == 0) {
            flag  = 0;
            state = 1;
        }
    }
    // USBSerial.printf("%d %d\n\r", state, flag);
    return state;
}

uint8_t check_alt_mode_change(void) {
    uint8_t state;
    static uint8_t flag = 0;
    state               = 0;
    if (flag == 0) {
        if (getModeButton() == 1) {
            flag = 1;
        }
    } else {
        if (getModeButton() == 0) {
            flag  = 0;
            state = 1;
        }
    }
    // USBSerial.printf("%d %d\n\r", state, flag);
    return state;
}

void loop() {
    uint16_t _throttle;  // = getThrottle();
    uint16_t _phi;       // = getAileron();
    uint16_t _theta;     // = getElevator();
    uint16_t _psi;       // = getRudder();

    while (Loop_flag == 0);
    Loop_flag = 0;
    etime     = stime;
    stime     = micros();
    dtime     = stime - etime;
    M5.update();
    joy_update();

    // Stop Watch Start&Stop&Reset
    if (M5.Btn.wasPressed() == true) {
        if (Timer_state == 0)
            Timer_state = 1;
        else if (Timer_state == 1)
            Timer_state = 0;
    }

    if (M5.Btn.pressedFor(400) == true) {
        Timer_state = 2;
    }

    if (Timer_state == 1) {
        // カウントアップ
        Timer = Timer + dTime;
    } else if (Timer_state == 2) {
        // タイマリセット
        Timer       = 0.0;
        Timer_state = 0;
    }

    _throttle = getThrottle();
    _phi      = getAileron();
    _theta    = getElevator();
    _psi      = getRudder();

    if (auto_up_down_status && (page_nums == PAGE_RUNNING)) {
        // Throttle_bias = _throttle;
        Phi_bias   = _phi;
        Theta_bias = _theta;
        Psi_bias   = _psi;
    }

    // mass pro
    // Throttle = (float)(_throttle - Throttle_bias)/(float)(RESO10BIT*0.5);
    Throttle = -(float)(_throttle - Throttle_bias) / (float)(RESO10BIT * 0.5);
    Phi      = (float)(_phi - Phi_bias) / (float)(RESO10BIT * 0.5);
    // Theta = -(float)(_theta - Theta_bias)/(float)(RESO10BIT*0.5);
    Theta = (float)(_theta - Theta_bias) / (float)(RESO10BIT * 0.5);
    Psi   = (float)(_psi - Psi_bias) / (float)(RESO10BIT * 0.5);

    uint8_t *d_int;

    // ブロードキャストの混信を防止するためこの機体のMACアドレスに送られてきたものか判断する
    senddata[0] = peerInfo.peer_addr[3];  ////////////////////////////
    senddata[1] = peerInfo.peer_addr[4];  ////////////////////////////
    senddata[2] = peerInfo.peer_addr[5];  ////////////////////////////

    d_int       = (uint8_t *)&Psi;
    senddata[3] = d_int[0];
    senddata[4] = d_int[1];
    senddata[5] = d_int[2];
    senddata[6] = d_int[3];

    d_int        = (uint8_t *)&Throttle;
    senddata[7]  = d_int[0];
    senddata[8]  = d_int[1];
    senddata[9]  = d_int[2];
    senddata[10] = d_int[3];

    d_int        = (uint8_t *)&Phi;
    senddata[11] = d_int[0];
    senddata[12] = d_int[1];
    senddata[13] = d_int[2];
    senddata[14] = d_int[3];

    d_int        = (uint8_t *)&Theta;
    senddata[15] = d_int[0];
    senddata[16] = d_int[1];
    senddata[17] = d_int[2];
    senddata[18] = d_int[3];

    senddata[19] = auto_up_down_status;
    senddata[20] = getFlipButton();
    senddata[21] = Mode;
    senddata[22] = AltMode;

    senddata[23] = proactive_flag;

    // checksum
    senddata[24] = 0;
    for (uint8_t i = 0; i < 24; i++) senddata[24] = senddata[24] + senddata[i];

    // 送信
    esp_err_t result = esp_now_send(peerInfo.peer_addr, senddata, sizeof(senddata));
#ifdef DEBUG
    USBSerial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n", peerInfo.peer_addr[0], peerInfo.peer_addr[1],
                     peerInfo.peer_addr[2], peerInfo.peer_addr[3], peerInfo.peer_addr[4], peerInfo.peer_addr[5]);
#endif
    // Display information
    // float vbat =0.0;// M5.Axp.GetBatVoltage();
    // int8_t bat_charge_p = int8_t((vbat - 3.0) / 1.2 * 100);

    // Reset
    if (/*M5.Axp.GetBtnPress() == 2*/ 0) {
        // 電源ボタンクリック
        // M5.Lcd.println("AtomFly2.0");
        esp_restart();
    }
    if (auto_up_down_status) {
        auto_up_down_status_counter++;
        if (auto_up_down_status_counter > 20) {
            auto_up_down_status_counter = 0;
            auto_up_down_status         = 0;
        }
    }
    if (proactive_flag) {
        proactive_flag_counter++;
        if (proactive_flag_counter > 20) {
            proactive_flag_counter = 0;
            proactive_flag         = 0;
        }
    }
    if (is_fly_flag) {
        is_fly_flag_counter++;
        if (is_fly_flag_counter > 2000) {
            is_fly_flag_counter = 0;
            is_fly_flag         = 0;
        }
    }
}

void show_battery_info() {
#if 0
  // バッテリー電圧表示
  double vbat = 0.0;
  int8_t bat_charge_p = 0;

  vbat = M5.Axp.GetBatVoltage();
  M5.Lcd.setCursor(5, 100);
  //M5.Lcd.setTextSize(1);
  M5.Lcd.printf("Volt:\n %8.2fV", vbat);

  // バッテリー残量表示
  bat_charge_p = int8_t((vbat - 3.0) / 1.2 * 100);
  M5.Lcd.setCursor(5, 140);
  M5.Lcd.printf("Charge:\n %8d%%", bat_charge_p);
#endif
}

void voltage_print(void) {
    // M5.Lcd.setCursor(0, 17, 2);
    // M5.Lcd.printf("%3.1fV", Battery_voltage);
}

void task_tone(void *pvParameters) {
    for (;;) {
        start_tone();
        vTaskDelete(task_tone_handle);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
