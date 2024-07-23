/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef APP_LVGL_H
#define APP_LVGL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

enum { PAGE_SETUP = 0, PAGE_RUNNING };

typedef struct {
    lv_obj_t *screen;
    bool screen_del;
    lv_obj_t *screen_img_1;
    lv_obj_t *screen_img_2;
    lv_obj_t *screen_cont_2;
    lv_obj_t *screen_cont_3;
    lv_obj_t *screen_cont_1;
    lv_obj_t *screen_label_1;
    lv_obj_t *screen_cont_4;
    lv_obj_t *screen_label_2;
    lv_obj_t *screen_btn_1;
    lv_obj_t *screen_btn_1_label;
    lv_obj_t *screen_running;
    bool screen_running_del;
    lv_obj_t *screen_running_img_1;
    lv_obj_t *screen_running_img_4;
    lv_obj_t *screen_running_img_6;
    lv_obj_t *screen_running_img_5;
    lv_obj_t *screen_running_img_7;
    lv_obj_t *screen_running_img_8;
    lv_obj_t *screen_running_cont_2;
    lv_obj_t *screen_running_cont_6;
    lv_obj_t *screen_running_label_2;
    lv_obj_t *screen_running_label_1;
    lv_obj_t *screen_running_btn_1;
    lv_obj_t *screen_running_btn_1_label;
    lv_obj_t *screen_running_cont_3;
    lv_obj_t *screen_running_label_3;
    lv_obj_t *screen_running_label_6;
    lv_obj_t *screen_running_cont_4;
    lv_obj_t *screen_running_label_4;
    lv_obj_t *screen_running_label_7;
    lv_obj_t *screen_running_cont_5;
    lv_obj_t *screen_running_label_5;
    lv_obj_t *screen_running_label_8;
    lv_obj_t *screen_running_btn_5;
    lv_obj_t *screen_running_btn_5_label;
} lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui *ui);

extern lv_ui guider_ui;
extern volatile uint8_t page_nums;

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);
void setup_scr_screen_running(lv_ui *ui);
void update_pitch_and_roll(lv_obj_t *ui_img_pitch_scale, lv_obj_t *ui_img_roll_scale, lv_obj_t *ui_Label_pitch,
                           lv_obj_t *ui_Label_roll, int pitch_value, int pitch_rotation, int roll_value);

LV_IMG_DECLARE(_StableMode_alpha_64x75);
LV_IMG_DECLARE(_Alt_Manual_alpha_64x75);
LV_IMG_DECLARE(_SportMode_alpha_64x75);
LV_IMG_DECLARE(_AutoMode_alpha_64x75);
LV_IMG_DECLARE(_Dial_bg_alpha_60x60);
LV_IMG_DECLARE(_Pitch_Scale_alpha_60x60);
LV_IMG_DECLARE(_Pointer_alpha_30x30);
LV_IMG_DECLARE(_Roll_Scale_alpha_80x80);
LV_IMG_DECLARE(_Dial_2_alpha_70x70);
LV_IMG_DECLARE(_mask_3_alpha_128x70);

LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_10)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)

#ifdef __cplusplus
}
#endif
#endif