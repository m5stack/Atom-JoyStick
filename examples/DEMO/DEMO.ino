#include "ATOM_FLY_REMOTER.h"
#include <M5GFX.h>
#include <M5AtomS3.h>
#include "fly_remoter_fw.h"

#define OPC_READ  (uint8_t)(0x03)
#define OPC_WREN  (uint8_t)(0x06)
#define OPC_ERPG  (uint8_t)(0x20)
#define OPC_ERUSM (uint8_t)(0x44)
#define OPC_USRCD (uint8_t)(0x77)

#define FW_SIZE 1024 * 10

volatile uint8_t flag_upgrade = 0;

M5GFX display;

ATOM_FLY_REMOTER remoter;

#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

uint16_t tone_set[] = {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4,
                       NOTE_D5, NOTE_D6, NOTE_D7};

#define buzzer (5)
int freq       = 2000;  //设置频率
int channel    = 0;     //通道号，取值0 ~ 15
int resolution = 8;     //计数位数，2的8次幂=256

float battery_voltage          = 0.0f;
uint16_t joy1_x_adc_color_flag = 0;
uint16_t joy1_y_adc_color_flag = 0;
uint16_t joy2_x_adc_color_flag = 0;
uint16_t joy2_y_adc_color_flag = 0;
uint16_t joy1_x_adc_value      = 0;
uint16_t joy1_y_adc_value      = 0;
uint16_t joy2_x_adc_value      = 0;
uint16_t joy2_y_adc_value      = 0;
uint16_t last_joy1_x_adc_value = 0;
uint16_t last_joy1_y_adc_value = 0;
uint16_t last_joy2_x_adc_value = 0;
uint16_t last_joy2_y_adc_value = 0;
uint8_t btn1_status            = 1;
uint8_t btn2_status            = 1;
uint8_t btnA_status            = 1;
uint8_t btnB_status            = 1;

TaskHandle_t lcd_display_task_handle;

void task_lcd_display(void* pvParameters) {
    for (;;) {
        display.startWrite();
        display.setCursor(0, 0);
        display.setTextColor(GREEN);
        display.setTextSize(3);
        display.fillRect(0, 0, 128, 25, BLACK);
        display.printf("%.2fV", battery_voltage);

        display.drawFastHLine(0, 25, 128, ORANGE);
        display.setCursor(0, 30);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.printf("        X        Y");
        display.setCursor(0, 40);
        display.setTextSize(1);
        display.printf("Joy1");
        display.setTextSize(2);

        int16_t adc_delta_x1 = joy1_x_adc_value > last_joy1_x_adc_value
                                   ? (joy1_x_adc_value - last_joy1_x_adc_value)
                                   : (last_joy1_x_adc_value - joy1_x_adc_value);

        if (adc_delta_x1 > 100) {
            last_joy1_x_adc_value = joy1_x_adc_value;
            if (joy1_x_adc_color_flag) {
                joy1_x_adc_color_flag = 0;
                display.setTextColor(YELLOW);
            } else {
                joy1_x_adc_color_flag = 1;
                display.setTextColor(RED);
            }
        } else {
            joy1_x_adc_color_flag = 0;
            display.setTextColor(YELLOW);
        }
        display.fillRect(23, 40, 70, 15, BLACK);
        display.printf("%d", joy1_x_adc_value);
        display.setCursor(80, 40);
        display.setTextSize(2);

        int16_t adc_delta_y1 = joy1_y_adc_value > last_joy1_y_adc_value
                                   ? (joy1_y_adc_value - last_joy1_y_adc_value)
                                   : (last_joy1_y_adc_value - joy1_y_adc_value);

        if (adc_delta_y1 > 100) {
            last_joy1_y_adc_value = joy1_y_adc_value;
            if (joy1_y_adc_color_flag) {
                joy1_y_adc_color_flag = 0;
                display.setTextColor(YELLOW);
            } else {
                joy1_y_adc_color_flag = 1;
                display.setTextColor(BLUE);
            }
        } else {
            joy1_y_adc_color_flag = 0;
            display.setTextColor(YELLOW);
        }
        display.fillRect(70, 40, 60, 15, BLACK);
        display.printf("%d", joy1_y_adc_value);

        display.setCursor(0, 60);
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.printf("Joy2");
        display.setTextSize(2);

        int16_t adc_delta_x2 = joy2_x_adc_value > last_joy2_x_adc_value
                                   ? (joy2_x_adc_value - last_joy2_x_adc_value)
                                   : (last_joy2_x_adc_value - joy2_x_adc_value);

        if (adc_delta_x2 > 100) {
            last_joy2_x_adc_value = joy2_x_adc_value;
            if (joy2_x_adc_color_flag) {
                joy2_x_adc_color_flag = 0;
                display.setTextColor(GREEN);
            } else {
                joy2_x_adc_color_flag = 1;
                display.setTextColor(RED);
            }
        } else {
            joy2_x_adc_color_flag = 0;
            display.setTextColor(GREEN);
        }
        display.fillRect(23, 60, 70, 15, BLACK);
        display.printf("%d", joy2_x_adc_value);
        display.setCursor(80, 60);
        display.setTextSize(2);

        int16_t adc_delta_y2 = joy2_y_adc_value > last_joy2_y_adc_value
                                   ? (joy2_y_adc_value - last_joy2_y_adc_value)
                                   : (last_joy2_y_adc_value - joy2_y_adc_value);

        if (adc_delta_y2 > 100) {
            last_joy2_y_adc_value = joy2_y_adc_value;
            if (joy2_y_adc_color_flag) {
                joy2_y_adc_color_flag = 0;
                display.setTextColor(GREEN);
            } else {
                joy2_y_adc_color_flag = 1;
                display.setTextColor(BLUE);
            }
        } else {
            joy2_y_adc_color_flag = 0;
            display.setTextColor(GREEN);
        }
        display.fillRect(70, 60, 60, 15, BLACK);
        display.printf("%d", joy2_y_adc_value);

        display.drawFastHLine(0, 75, 128, ORANGE);
        display.setCursor(0, 90);
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.printf("Btn1       Btn2");
        if (!btn1_status) {
            display.fillRect(35, 85, 15, 15, GREEN);
        } else {
            display.fillRect(35, 85, 15, 15, RED);
        }
        if (!btn2_status) {
            display.fillRect(100, 85, 15, 15, GREEN);
        } else {
            display.fillRect(100, 85, 15, 15, RED);
        }
        display.setCursor(0, 110);
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.printf("BtnA       BtnB");
        if (!btnA_status) {
            display.fillRect(35, 105, 15, 15, GREEN);
        } else {
            display.fillRect(35, 105, 15, 15, RED);
        }
        if (!btnB_status) {
            display.fillRect(100, 105, 15, 15, GREEN);
        } else {
            display.fillRect(100, 105, 15, 15, RED);
        }
        display.endWrite();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void func_iap_upgrade(void) {
    uint8_t error = 1;
    uint8_t sendbuffer[1032];
    uint16_t loop         = 0;
    uint16_t buffer_index = 0;  //*endp;

    uint32_t APPLICATION_ADDRESS = 0x08001000;
    uint32_t sendbuffer_Size     = 0;

    sendbuffer_Size = FW_SIZE;

    Serial.printf("begin\r\n");

    do {
        /*Fille data in to buffuer*/
        sendbuffer[0] = OPC_WREN; /*Command Code*/

        /*Address*/
        sendbuffer[1] = (uint8_t)(APPLICATION_ADDRESS >> 24);
        sendbuffer[2] = (uint8_t)(APPLICATION_ADDRESS >> 16);
        sendbuffer[3] = (uint8_t)(APPLICATION_ADDRESS >> 8);
        sendbuffer[4] = (uint8_t)(APPLICATION_ADDRESS >> 0);

        if (sendbuffer_Size >= 1024) {
            sendbuffer[5] = 0x04;
            sendbuffer[6] = 0x0;
            do {
                sendbuffer[8 + loop] = _acFly_Remoter[buffer_index++];
                Serial.printf("%02X,", sendbuffer[8 + loop]);
                loop++;
            } while (loop < 1024);

        } else {
            sendbuffer[5] = (uint8_t)(sendbuffer_Size >> 8);
            sendbuffer[6] = (uint8_t)(sendbuffer_Size >> 0);
            do {
                sendbuffer[8 + loop] = _acFly_Remoter[buffer_index++];
                Serial.printf("%02X,", sendbuffer[8 + loop]);
                loop++;
            } while (loop < sendbuffer_Size);
        }
        Serial.println();

        sendbuffer[7] = 0xFF;
        loop          = 0;
        if (sendbuffer_Size >= 1024) {
            Wire.beginTransmission(0x54);
            error = Wire.endTransmission();
            while (error) {
                Wire.beginTransmission(0x54);
                error = Wire.endTransmission();
                Serial.printf("fuck\r\n");
            }
            Wire.beginTransmission(0x54);
            Wire.write(sendbuffer, 1032);
            Wire.endTransmission();
            sendbuffer_Size -= 1024;
            APPLICATION_ADDRESS += 1024;
            //*temp +=128;
        } else {
            Wire.beginTransmission(0x54);
            error = Wire.endTransmission();
            while (error) {
                Wire.beginTransmission(0x54);
                error = Wire.endTransmission();
            }
            Wire.beginTransmission(0x54);
            Wire.write(sendbuffer, sendbuffer_Size + 8);
            Wire.endTransmission();
            sendbuffer_Size = 0;
        }
        delay(200);
    } while (sendbuffer_Size > 0);
    Wire.beginTransmission(0x54);
    error = Wire.endTransmission();
    while (error) {
        Wire.beginTransmission(0x54);
        error = Wire.endTransmission();
    }
    Wire.beginTransmission(0x54);
    Wire.write(OPC_USRCD);
    Wire.endTransmission();
    Wire.setBufferSize(128);
}

void func_iap_update(void) {
    pinMatrixOutDetach(38, false, false);
    pinMatrixInDetach(30, false, false);
    pinMatrixOutDetach(39, false, false);
    pinMatrixInDetach(29, false, false);
    pinMode(38, OUTPUT);
    pinMode(39, OUTPUT);
    digitalWrite(38, LOW);
    digitalWrite(39, LOW);
}

void page_iap_upgrade(void) {
    int error = -1;

    display.startWrite();
    display.clear(BLACK);
    display.setTextSize(2);
    display.setTextColor(ORANGE);
    display.drawString("IAP Upgrade", 0, 0);
    display.setColor(ORANGE);
    display.drawFastHLine(0, 25, 128);
    display.endWrite();

    remoter.jumpBootloader();
    func_iap_update();

    delay(3000);
    digitalWrite(39, HIGH);
    pinMode(39, OPEN_DRAIN | PULLUP | INPUT | OUTPUT);
    pinMatrixOutAttach(39, 29, false, false);
    pinMatrixInAttach(39, 29, false);
    digitalWrite(38, HIGH);
    pinMode(38, OPEN_DRAIN | PULLUP | INPUT | OUTPUT);
    pinMatrixOutAttach(38, 30, false, false);
    pinMatrixInAttach(38, 30, false);
    // remoter.begin(&Wire, ATOM_FLY_REMOTER_ADDR, 38, 39, 100000U);
    while (1) {
        // display.startWrite();
        // display.setCursor(0, 30);
        for (int i = 1; i < 127; i++) {
            Wire.beginTransmission(i);
            error = Wire.endTransmission();
            if (error == 0) {
                USBSerial.printf("0x%X; ", i);
            } else {
                USBSerial.printf("fuck%d\r\n", error);
            }
        }
        // display.endWrite();
    }

    // if (flag_upgrade == 1) {
    //     Wire.beginTransmission(0x54);
    //     error = Wire.endTransmission();
    // }

    // if (error == 0) {
    //     display.setTextColor(RED);
    //     display.drawString("Upgrading..", 0, 30);
    //     func_iap_upgrade();

    //     delay(1000);
    //     Wire.beginTransmission(ATOM_FLY_REMOTER_ADDR);
    //     error = Wire.endTransmission();
    //     if (error == 0) {
    //     flag_upgrade = 2;
    //     } else {
    //     flag_upgrade = 3;
    //     }
    //     error = -1;
    // } else {

    // }

    // switch (flag_upgrade)
    // {
    // case 2:
    //     display.setTextColor(GREEN);
    //     display.drawString("success,fw:" +
    //     String(remoter.getFirmwareVersion()), 0, 70); break;
    // case 3:
    //     display.setTextColor(RED);
    //     display.drawString("failed,try again", 0, 70);
    //     break;

    // default:
    //     break;
    // }
    // display.endWrite();
}

void setup() {
    display.begin();
    display.setEpdMode(epd_mode_t::epd_fastest);
    display.setColorDepth(8);  // mono color
    //   display.setFont(&fonts::Font4);
    display.setTextSize(2);
    display.clear(TFT_BLACK);
    M5.begin(false, true, false,
             false);  // Init M5AtomS3(Initialization of internal I2C is also
    //                   // included).  M5AtomS3(初始化内部I2C也包含在内)
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(buzzer, channel);
    ledcWrite(channel, 200);
    ledcWriteTone(channel, 0);
    remoter.begin(&Wire, ATOM_FLY_REMOTER_ADDR, 38, 39, 100000U);
    remoter.setSystemReset();
    delay(1300);                                       // Delay must be 1300
    xTaskCreatePinnedToCore(task_lcd_display,          //任务函数
                            "TaskLcdDisplay",          //任务名称
                            8096,                      //堆栈大小
                            NULL,                      //传递参数
                            1,                         //任务优先级
                            &lcd_display_task_handle,  //任务句柄
                            0);  //无关联，不绑定在任何一个核上
}

void loop() {
    battery_voltage  = remoter.getBatteryVoltage();
    joy1_x_adc_value = remoter.getJoy1ADCValueX(_12bit);
    joy1_y_adc_value = remoter.getJoy1ADCValueY(_12bit);
    joy2_x_adc_value = remoter.getJoy2ADCValueX(_12bit);
    joy2_y_adc_value = remoter.getJoy2ADCValueY(_12bit);
    btn1_status      = remoter.getButtonValue(BUTTON_1);
    btn2_status      = remoter.getButtonValue(BUTTON_2);
    btnA_status      = remoter.getButtonValue(BUTTON_A);
    btnB_status      = remoter.getButtonValue(BUTTON_B);
    M5.update();
    if (M5.Btn.read()) {
        unsigned long press_timestamp = millis();
        while (M5.Btn.read())
            ;
        unsigned long press_time = millis() - press_timestamp;

        if (press_time >= 100 && press_time <= 300) {
            for (int i = 0; i < sizeof(tone_set) / sizeof(tone_set[0]); i++) {
                ledcWriteTone(channel, tone_set[i]);
                delay(150);
            }
            ledcWriteTone(channel, 0);
        }
        // else if (press_time >= 500) {
        //     USBSerial.println("fuck long");
        //     vTaskSuspend(lcd_display_task_handle);
        //     page_iap_upgrade();
        //     // display.startWrite();
        //     // display.clear(BLACK);
        //     // display.endWrite();
        //     // vTaskResume(lcd_display_task_handle);
        // }
    }
}
