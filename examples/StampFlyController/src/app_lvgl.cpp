/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "app_lvgl.h"
#include "main.h"

lv_ui guider_ui;
static lv_timer_t *screen_update_data_task;
static lv_timer_t *screen_running_update_data_task;
static uint8_t long_press_flag = 0;
volatile uint8_t page_nums     = PAGE_SETUP;

void screen_timer_cb(lv_timer_t *t);
void screen_running_timer_cb(lv_timer_t *t);

void update_pitch(lv_obj_t *ui_img_pitch_scale, lv_obj_t *ui_Label_pitch, int pitch_value, int pitch_rotation) {
    // Calculate the rotation angle in degrees for pitch
    int rotation_angle = pitch_rotation / 10;                   // Each 100 units corresponds to 10 degrees
    lv_img_set_angle(ui_img_pitch_scale, rotation_angle * 10);  // LVGL uses 0.1 degree units

    // Calculate the Y position
    int y_position = pitch_value;  // Each 10 pixels corresponds to 5 units
    lv_obj_set_y(ui_img_pitch_scale, y_position);

    // Update the pitch label with the current pitch value
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", pitch_value);
    // lv_label_set_text(ui_Label_pitch, buf);
}

void update_roll(lv_obj_t *ui_img_roll_scale, lv_obj_t *ui_Label_roll, int roll_value) {
    // Calculate the rotation angle in degrees
    int rotation_angle = roll_value;                           // Each unit corresponds to 1 degree
    lv_img_set_angle(ui_img_roll_scale, rotation_angle * 10);  // LVGL uses 0.1 degree units

    // Display positive degree on the right and negative degree on the left
    int display_angle = -roll_value;  // Invert the roll value for display

    // Update the roll label with the current rotation angle in degrees
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", display_angle);
    // lv_label_set_text(ui_Label_roll, buf);
}

void update_pitch_and_roll(lv_obj_t *ui_img_pitch_scale, lv_obj_t *ui_img_roll_scale, lv_obj_t *ui_Label_pitch,
                           lv_obj_t *ui_Label_roll, int pitch_value, int pitch_rotation, int roll_value) {
    update_pitch(ui_img_pitch_scale, ui_Label_pitch, pitch_value, pitch_rotation);
    update_roll(ui_img_roll_scale, ui_Label_roll, roll_value);
}

void mock_data(int &pitch_value, int &pitch_rotation, int &roll_value, int speed_factor) {
    static bool increasing_pitch          = true;
    static bool increasing_pitch_rotation = true;
    static bool increasing_roll           = true;

    // Update pitch
    if (increasing_pitch) {
        pitch_value += speed_factor;
        if (pitch_value >= 91) {  // 20 units is the max pitch value
            increasing_pitch = false;
        }
    } else {
        pitch_value -= speed_factor;
        if (pitch_value <= -29) {  // -20 units is the min pitch value
            increasing_pitch = true;
        }
    }

    // Update pitch rotation
    if (increasing_pitch_rotation) {
        pitch_rotation += 10 * speed_factor;
        if (pitch_rotation >= 900) {  // 900 units is the max pitch rotation
            increasing_pitch_rotation = false;
        }
    } else {
        pitch_rotation -= 10 * speed_factor;
        if (pitch_rotation <= -900) {  // -900 units is the min pitch rotation
            increasing_pitch_rotation = true;
        }
    }

    // Update roll
    if (increasing_roll) {
        roll_value -= speed_factor;  // Decrease roll value for right rotation
        if (roll_value <= -90) {     // -90 degrees is the max right roll value
            increasing_roll = false;
        }
    } else {
        roll_value += speed_factor;  // Increase roll value for left rotation
        if (roll_value >= 90) {      // 90 degrees is the max left roll value
            increasing_roll = true;
        }
    }
}

void init_scr_del_flag(lv_ui *ui) {
    ui->screen_del         = true;
    ui->screen_running_del = true;
}

void ui_load_scr_animation(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, bool *old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del) {
    lv_obj_t *act_scr = lv_scr_act();
    lv_disp_t *d      = lv_obj_get_disp(act_scr);
    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
#if LV_USE_FREEMASTER
        if (auto_del) {
            gg_edata_task_clear(act_scr);
        }
#endif
        if (auto_del && is_clean) {
            lv_obj_clean(act_scr);
        }
        if (new_scr_del) {
            setup_scr(ui);
        }
        lv_scr_load_anim(*new_scr, anim_type, time, delay, auto_del);
        *old_scr_del = auto_del;
    }
}

static void screen_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_SCREEN_LOADED: {
            page_nums               = PAGE_SETUP;
            screen_update_data_task = lv_timer_create(screen_timer_cb, 100, &guider_ui);
            break;
        }
        case LV_EVENT_SCREEN_UNLOADED: {
            lv_timer_del(screen_update_data_task);
            break;
        }
        default:
            break;
    }
}

static void screen_btn_1_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_CLICKED: {
            if (!long_press_flag) {
                beep();
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_running, guider_ui.screen_running_del,
                                      &guider_ui.screen_del, setup_scr_screen_running, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0,
                                      false, true);
            }
            long_press_flag = 0;
            break;
        }
        default:
            break;
    }
}

void events_init_screen(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, NULL);
}

void setup_scr_screen(lv_ui *ui) {
    // Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 128, 128);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_img_1
    ui->screen_img_1 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_1, &_StableMode_alpha_64x75);
    lv_img_set_pivot(ui->screen_img_1, 50, 50);
    lv_img_set_angle(ui->screen_img_1, 0);
    lv_obj_set_pos(ui->screen_img_1, 0, 0);
    lv_obj_set_size(ui->screen_img_1, 64, 75);

    // Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_img_2
    ui->screen_img_2 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_2, &_Alt_Manual_alpha_64x75);
    lv_img_set_pivot(ui->screen_img_2, 50, 50);
    lv_img_set_angle(ui->screen_img_2, 0);
    lv_obj_set_pos(ui->screen_img_2, 64, 0);
    lv_obj_set_size(ui->screen_img_2, 64, 75);

    // Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_2
    ui->screen_cont_2 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_2, 0, 75);
    lv_obj_set_size(ui->screen_cont_2, 64, 36);
    lv_obj_set_scrollbar_mode(ui->screen_cont_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_2, lv_color_hex(0x45d7fc), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_3
    ui->screen_cont_3 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_3, 64, 75);
    lv_obj_set_size(ui->screen_cont_3, 64, 36);
    lv_obj_set_scrollbar_mode(ui->screen_cont_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_3, lv_color_hex(0xfc6ab3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_1
    ui->screen_cont_1 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_1, 3, 77);
    lv_obj_set_size(ui->screen_cont_1, 122, 15);
    lv_obj_set_scrollbar_mode(ui->screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_1, "BAT1:");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_1, 1, 0);
    lv_obj_set_size(ui->screen_label_1, 128, 15);

    // Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_montserratMedium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_4
    ui->screen_cont_4 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_4, 3, 94);
    lv_obj_set_size(ui->screen_cont_4, 122, 15);
    lv_obj_set_scrollbar_mode(ui->screen_cont_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_2
    ui->screen_label_2 = lv_label_create(ui->screen_cont_4);
    lv_label_set_text(ui->screen_label_2, "BAT2:");
    lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_2, 0, 0);
    lv_obj_set_size(ui->screen_label_2, 128, 15);

    // Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_2, &lv_font_montserratMedium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_btn_1
    ui->screen_btn_1       = lv_btn_create(ui->screen);
    ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1);
    lv_label_set_text(ui->screen_btn_1_label, "Press to Next");
    lv_label_set_long_mode(ui->screen_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_btn_1, 0, 111);
    lv_obj_set_size(ui->screen_btn_1, 128, 17);

    // Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of screen.

    // Update current screen layout.
    lv_obj_update_layout(ui->screen);

    events_init_screen(ui);
}

static void screen_running_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_SCREEN_LOADED: {
            page_nums      = PAGE_RUNNING;
            proactive_flag = 1;
            lv_label_set_text(guider_ui.screen_running_label_1, " ");
            lv_img_set_pivot(guider_ui.screen_running_img_5, 40, 40);
            lv_img_set_pivot(guider_ui.screen_running_img_4, 30, 30);
            screen_running_update_data_task = lv_timer_create(screen_running_timer_cb, 100, &guider_ui);
            break;
        }
        case LV_EVENT_SCREEN_UNLOADED: {
            if (fly_mode == FLIGHT_MODE) {
                auto_up_down_status = 1;
            }
            if (AltMode == NOT_ALT_CONTROL_MODE && fly_status_manual) {
                fly_status_manual   = 0;
                auto_up_down_status = 1;
            }
            lv_timer_del(screen_running_update_data_task);
            break;
        }
        default:
            break;
    }
}
static void screen_running_btn_1_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_CLICKED: {
            // fly

            if (AltMode == ALT_CONTROL_MODE && fly_mode == PARKING_MODE && !fly_status) {
                fly_status          = 1;
                auto_up_down_status = 1;
                beep();
            }
            if (AltMode == ALT_CONTROL_MODE && fly_mode == FLIGHT_MODE && fly_status) {
                fly_status          = 0;
                auto_up_down_status = 1;
                beep();
            }
            if (AltMode == NOT_ALT_CONTROL_MODE && !fly_status_manual) {
                fly_status_manual   = 1;
                auto_up_down_status = 1;
                beep();
            } else if (AltMode == NOT_ALT_CONTROL_MODE && fly_status_manual) {
                fly_status_manual   = 0;
                auto_up_down_status = 1;
                beep();
            }
            break;
        }
        // case LV_EVENT_LONG_PRESSED:
        // {
        // 	beep();
        // 	long_press_flag = 1;
        // 	ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_running_del,
        // setup_scr_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false, true); 	break;
        // }
        default:
            break;
    }
}
static void screen_running_btn_5_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_CLICKED: {
            beep();
            if (AltMode == NOT_ALT_CONTROL_MODE && fly_status_manual) {
                fly_status_manual   = 0;
                auto_up_down_status = 1;
            }
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_running_del,
                                  setup_scr_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false, true);
            break;
        }
        default:
            break;
    }
}
void events_init_screen_running(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_running, screen_running_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_running_btn_1, screen_running_btn_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_running_btn_5, screen_running_btn_5_event_handler, LV_EVENT_ALL, NULL);
}

void setup_scr_screen_running(lv_ui *ui) {
    // Write codes screen_running
    ui->screen_running = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_running, 128, 128);
    lv_obj_set_scrollbar_mode(ui->screen_running, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_running, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_1
    ui->screen_running_img_1 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_1, &_Dial_bg_alpha_60x60);
    lv_img_set_pivot(ui->screen_running_img_1, 50, 50);
    lv_img_set_angle(ui->screen_running_img_1, 0);
    lv_obj_set_pos(ui->screen_running_img_1, 13, 39);
    lv_obj_set_size(ui->screen_running_img_1, 60, 60);

    // Write style for screen_running_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_4
    ui->screen_running_img_4 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_4, &_Pitch_Scale_alpha_60x60);
    lv_img_set_pivot(ui->screen_running_img_4, 50, 50);
    lv_img_set_angle(ui->screen_running_img_4, 0);
    lv_obj_set_pos(ui->screen_running_img_4, 13, 39);
    lv_obj_set_size(ui->screen_running_img_4, 60, 60);

    // Write style for screen_running_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_6
    ui->screen_running_img_6 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_6, &_Pointer_alpha_30x30);
    lv_img_set_pivot(ui->screen_running_img_6, 50, 50);
    lv_img_set_angle(ui->screen_running_img_6, 0);
    lv_obj_set_pos(ui->screen_running_img_6, 28, 45);
    lv_obj_set_size(ui->screen_running_img_6, 30, 30);

    // Write style for screen_running_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_5
    ui->screen_running_img_5 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_5, &_Roll_Scale_alpha_80x80);
    lv_img_set_pivot(ui->screen_running_img_5, 50, 50);
    lv_img_set_angle(ui->screen_running_img_5, 0);
    lv_obj_set_pos(ui->screen_running_img_5, 3, 29);
    lv_obj_set_size(ui->screen_running_img_5, 80, 80);

    // Write style for screen_running_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_7
    ui->screen_running_img_7 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_7, &_Dial_2_alpha_70x70);
    lv_img_set_pivot(ui->screen_running_img_7, 50, 50);
    lv_img_set_angle(ui->screen_running_img_7, 0);
    lv_obj_set_pos(ui->screen_running_img_7, 8, 34);
    lv_obj_set_size(ui->screen_running_img_7, 70, 70);

    // Write style for screen_running_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_img_8
    ui->screen_running_img_8 = lv_img_create(ui->screen_running);
    lv_obj_add_flag(ui->screen_running_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_running_img_8, &_mask_3_alpha_128x70);
    lv_img_set_pivot(ui->screen_running_img_8, 50, 50);
    lv_img_set_angle(ui->screen_running_img_8, 0);
    lv_obj_set_pos(ui->screen_running_img_8, -21, 34);
    lv_obj_set_size(ui->screen_running_img_8, 128, 70);

    // Write style for screen_running_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->screen_running_img_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_cont_2
    ui->screen_running_cont_2 = lv_obj_create(ui->screen_running);
    lv_obj_set_pos(ui->screen_running_cont_2, 0, 0);
    lv_obj_set_size(ui->screen_running_cont_2, 90, 34);
    lv_obj_set_scrollbar_mode(ui->screen_running_cont_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_cont_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_cont_6
    ui->screen_running_cont_6 = lv_obj_create(ui->screen_running);
    lv_obj_set_pos(ui->screen_running_cont_6, 0, 104);
    lv_obj_set_size(ui->screen_running_cont_6, 90, 24);
    lv_obj_set_scrollbar_mode(ui->screen_running_cont_6, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_cont_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_cont_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_2
    ui->screen_running_label_2 = lv_label_create(ui->screen_running);
    lv_label_set_text(ui->screen_running_label_2, "20");
    lv_label_set_long_mode(ui->screen_running_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_2, 0, 17);
    lv_obj_set_size(ui->screen_running_label_2, 90, 20);

    // Write style for screen_running_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_2, &lv_font_montserratMedium_16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_1
    ui->screen_running_label_1 = lv_label_create(ui->screen_running);
    lv_label_set_text(ui->screen_running_label_1, "  ");
    lv_label_set_long_mode(ui->screen_running_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_1, 0, 5);
    lv_obj_set_size(ui->screen_running_label_1, 90, 20);

    // Write style for screen_running_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_1, &lv_font_montserratMedium_12,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_btn_1
    ui->screen_running_btn_1       = lv_btn_create(ui->screen_running);
    ui->screen_running_btn_1_label = lv_label_create(ui->screen_running_btn_1);
    lv_label_set_text(ui->screen_running_btn_1_label, "Press to Fly");
    lv_label_set_long_mode(ui->screen_running_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_running_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_running_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_running_btn_1, 0, 108);
    lv_obj_set_size(ui->screen_running_btn_1, 128, 20);

    // Write style for screen_running_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_running_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_btn_1, lv_color_hex(0x33cc99), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_running_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_cont_3
    ui->screen_running_cont_3 = lv_obj_create(ui->screen_running);
    lv_obj_set_pos(ui->screen_running_cont_3, 90, 0);
    lv_obj_set_size(ui->screen_running_cont_3, 38, 38);
    lv_obj_set_scrollbar_mode(ui->screen_running_cont_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_cont_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_cont_3, lv_color_hex(0xff6633), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_3
    ui->screen_running_label_3 = lv_label_create(ui->screen_running_cont_3);
    lv_label_set_text(ui->screen_running_label_3, "Fly\nBAT:");
    lv_label_set_long_mode(ui->screen_running_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_3, 0, 0);
    lv_obj_set_size(ui->screen_running_label_3, 38, 20);

    // Write style for screen_running_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_3, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_6
    ui->screen_running_label_6 = lv_label_create(ui->screen_running_cont_3);
    lv_label_set_text(ui->screen_running_label_6, "3.7V");
    lv_label_set_long_mode(ui->screen_running_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_6, 0, 24);
    lv_obj_set_size(ui->screen_running_label_6, 38, 10);

    // Write style for screen_running_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_6, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_cont_4
    ui->screen_running_cont_4 = lv_obj_create(ui->screen_running);
    lv_obj_set_pos(ui->screen_running_cont_4, 90, 38);
    lv_obj_set_size(ui->screen_running_cont_4, 38, 35);
    lv_obj_set_scrollbar_mode(ui->screen_running_cont_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_cont_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_cont_4, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_cont_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_4
    ui->screen_running_label_4 = lv_label_create(ui->screen_running_cont_4);
    lv_label_set_text(ui->screen_running_label_4, "BAT1:");
    lv_label_set_long_mode(ui->screen_running_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_4, 0, 0);
    lv_obj_set_size(ui->screen_running_label_4, 38, 10);

    // Write style for screen_running_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_4, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_7
    ui->screen_running_label_7 = lv_label_create(ui->screen_running_cont_4);
    lv_label_set_text(ui->screen_running_label_7, "3.7V");
    lv_label_set_long_mode(ui->screen_running_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_7, 0, 18);
    lv_obj_set_size(ui->screen_running_label_7, 38, 10);

    // Write style for screen_running_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_7, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_7, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_cont_5
    ui->screen_running_cont_5 = lv_obj_create(ui->screen_running);
    lv_obj_set_pos(ui->screen_running_cont_5, 90, 73);
    lv_obj_set_size(ui->screen_running_cont_5, 38, 35);
    lv_obj_set_scrollbar_mode(ui->screen_running_cont_5, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_running_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_cont_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_running_cont_5, lv_color_hex(0xd5d5d5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_running_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_cont_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_5
    ui->screen_running_label_5 = lv_label_create(ui->screen_running_cont_5);
    lv_label_set_text(ui->screen_running_label_5, "BAT2:");
    lv_label_set_long_mode(ui->screen_running_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_5, 0, 0);
    lv_obj_set_size(ui->screen_running_label_5, 39, 10);

    // Write style for screen_running_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_5, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_label_8
    ui->screen_running_label_8 = lv_label_create(ui->screen_running_cont_5);
    lv_label_set_text(ui->screen_running_label_8, "3.7V");
    lv_label_set_long_mode(ui->screen_running_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_running_label_8, 0, 18);
    lv_obj_set_size(ui->screen_running_label_8, 38, 10);

    // Write style for screen_running_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_label_8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_label_8, &lv_font_montserratMedium_10,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_label_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_running_label_8, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_running_btn_5
    ui->screen_running_btn_5       = lv_btn_create(ui->screen_running);
    ui->screen_running_btn_5_label = lv_label_create(ui->screen_running_btn_5);
    lv_label_set_text(ui->screen_running_btn_5_label, "");
    lv_label_set_long_mode(ui->screen_running_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_running_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_running_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_running_btn_5, 75, 6);
    lv_obj_set_size(ui->screen_running_btn_5, 10, 10);

    // Write style for screen_running_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_running_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_running_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_running_btn_5, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_running_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_running_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_running_btn_5, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_running_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_running_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of screen_running.

    // Update current screen layout.
    lv_obj_update_layout(ui->screen_running);

    // Init events for screen.
    events_init_screen_running(ui);
}

void setup_ui(lv_ui *ui) {
    init_scr_del_flag(ui);
    setup_scr_screen(ui);
    lv_scr_load(ui->screen);
}

void screen_timer_cb(lv_timer_t *t) {
    if (check_control_mode_change() == 1) {
        beep();
        if (Mode == ANGLECONTROL)
            Mode = RATECONTROL;
        else
            Mode = ANGLECONTROL;
    }

    if (check_alt_mode_change() == 1) {
        beep();
        if (AltMode == ALT_CONTROL_MODE)
            AltMode = NOT_ALT_CONTROL_MODE;
        else
            AltMode = ALT_CONTROL_MODE;
    }

    lv_label_set_text_fmt(guider_ui.screen_label_1, "BAT1:%.1fV", Battery_voltage[0]);
    lv_label_set_text_fmt(guider_ui.screen_label_2, "BAT2:%.1fV", Battery_voltage[1]);

    // #ifdef NEW_ATOM_JOY
    // if (StickMode == 2) {
    // lv_label_set_text(guider_ui.screen_label_10, "Throttle: Left");
    // }
    // else if (StickMode == 3) {
    // lv_label_set_text(guider_ui.screen_label_10, "Throttle: Right");
    // }
    // #endif

    if (AltMode == ALT_CONTROL_MODE) {
        lv_img_set_src(guider_ui.screen_img_2, &_AutoMode_alpha_64x75);
        lv_obj_set_style_bg_color(guider_ui.screen_cont_3, lv_color_hex(0x61DF8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    } else if (AltMode == NOT_ALT_CONTROL_MODE) {
        lv_img_set_src(guider_ui.screen_img_2, &_Alt_Manual_alpha_64x75);
        lv_obj_set_style_bg_color(guider_ui.screen_cont_3, lv_color_hex(0xfc6ab3), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (Mode == ANGLECONTROL) {
        lv_img_set_src(guider_ui.screen_img_1, &_StableMode_alpha_64x75);
        lv_obj_set_style_bg_color(guider_ui.screen_cont_2, lv_color_hex(0x45d7fc), LV_PART_MAIN | LV_STATE_DEFAULT);
    } else if (Mode == RATECONTROL) {
        lv_img_set_src(guider_ui.screen_img_1, &_SportMode_alpha_64x75);
        lv_obj_set_style_bg_color(guider_ui.screen_cont_2, lv_color_hex(0xfcd741), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // if (peerInfo.peer_addr[4] == 0xFF && peerInfo.peer_addr[5] == 0xFF) {
    //     lv_obj_set_style_bg_color(guider_ui.screen_cont_10, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
    //     lv_label_set_text(guider_ui.screen_label_15, "No Fly");
    // }
    // else {
    //     lv_obj_set_style_bg_color(guider_ui.screen_cont_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    //     lv_label_set_text_fmt(guider_ui.screen_label_15, "%02X:%02X",
    //     peerInfo.peer_addr[4], peerInfo.peer_addr[5]);
    // }
}

void screen_running_timer_cb(lv_timer_t *t) {
    if (is_fly_flag) {
        lv_label_set_text_fmt(guider_ui.screen_running_label_1, "F-TOF:%.1fM", (float)tof_front / 1000.0f);
        lv_label_set_text_fmt(guider_ui.screen_running_label_2, "ALT:%.1fM", altitude);
        lv_label_set_text_fmt(guider_ui.screen_running_label_6, "%.1fV", fly_bat_voltage);
        lv_label_set_text_fmt(guider_ui.screen_running_label_7, "%.1fV", Battery_voltage[0]);
        lv_label_set_text_fmt(guider_ui.screen_running_label_8, "%.1fV", Battery_voltage[1]);

        if (fly_mode != last_fly_mode) {
            if (fly_mode == PARKING_MODE) fly_status = 0;
            last_fly_mode = fly_mode;
        }

        if (AltMode == ALT_CONTROL_MODE && fly_mode == PARKING_MODE) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0x33cc99),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0x0),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Press to Fly");
        } else if (AltMode == ALT_CONTROL_MODE && fly_mode == FLIGHT_MODE && alt_flag == 0 && fly_status) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0x8D0098),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0xffffff),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Taking Off");
        } else if (AltMode == ALT_CONTROL_MODE && fly_mode == FLIGHT_MODE && alt_flag == 1 && fly_status) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0xC1001D),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0xffffff),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Press to Land");
        } else if (AltMode == ALT_CONTROL_MODE && fly_mode == AUTO_LANDING_MODE) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0x007917),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0x0),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Landing");
        } else if (AltMode == NOT_ALT_CONTROL_MODE && fly_mode == PARKING_MODE) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0x33cc99),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0x0),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Press to Arm");
        } else if (AltMode == NOT_ALT_CONTROL_MODE && fly_mode == FLIGHT_MODE) {
            lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0xC1001D),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0xffffff),
                                        LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.screen_running_btn_1_label, "Press to Stop");
        }

        // Example updates for testing
        int pitch_value    = 39;
        int pitch_rotation = 0;
        int roll_value     = 0;

        // Simulate pitch and roll changes
        // int speed_factor = 1; // Adjust this value to control speed of mock data generation
        // mock_data(pitch_value, pitch_rotation, roll_value, speed_factor);

        roll_value     = (int)roll_angle;
        pitch_value    = (int)pitch_angle;
        pitch_rotation = (int)yaw_angle;
        pitch_value += 39;
        pitch_rotation += 180;
        pitch_rotation *= 10;

        update_pitch_and_roll(guider_ui.screen_running_img_4, guider_ui.screen_running_img_5,
                              guider_ui.screen_running_label_1, guider_ui.screen_running_label_2, pitch_value,
                              pitch_rotation, roll_value);
    } else {
        lv_label_set_text(guider_ui.screen_running_label_1, "F-TOF:-.-M");
        lv_label_set_text(guider_ui.screen_running_label_2, "ALT:-.-M");
        lv_label_set_text(guider_ui.screen_running_label_6, "-.-V");
        lv_label_set_text_fmt(guider_ui.screen_running_label_7, "%.1fV", Battery_voltage[0]);
        lv_label_set_text_fmt(guider_ui.screen_running_label_8, "%.1fV", Battery_voltage[1]);

        lv_obj_set_style_bg_color(guider_ui.screen_running_btn_1, lv_color_hex(0xC1001D),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.screen_running_btn_1, lv_color_hex(0xffffff),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(guider_ui.screen_running_btn_1_label, "No StampFly");

        int pitch_value    = 39;
        int pitch_rotation = 0;
        int roll_value     = 0;
        update_pitch_and_roll(guider_ui.screen_running_img_4, guider_ui.screen_running_img_5,
                              guider_ui.screen_running_label_1, guider_ui.screen_running_label_2, pitch_value,
                              pitch_rotation, roll_value);
    }
}
