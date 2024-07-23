/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "lvgl_porting.h"

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2 /*!< LVGL tick period in ms */
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (8 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     0

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[LCD_WIDTH * 20];
static lv_color_t buf2[LCD_WIDTH * 20];

SemaphoreHandle_t xGuiSemaphore;

TaskHandle_t task_lvgl_handle = NULL;

bool example_lvgl_lock(int timeout_ms) {
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTake(xGuiSemaphore, timeout_ticks) == pdTRUE;
}

void example_lvgl_unlock(void) {
    xSemaphoreGive(xGuiSemaphore);
}

static void example_lvgl_port_task(void *arg) {
    uint32_t task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
    setup_ui(&guider_ui);
    while (1) {
        /* Lock the mutex due to the LVGL APIs are not thread-safe */
        if (example_lvgl_lock(-1)) {
            M5.update();
            task_delay_ms = lv_timer_handler();
            /* Release the mutex */
            example_lvgl_unlock();
        }
        if (task_delay_ms > EXAMPLE_LVGL_TASK_MAX_DELAY_MS) {
            task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
        } else if (task_delay_ms < EXAMPLE_LVGL_TASK_MIN_DELAY_MS) {
            task_delay_ms = EXAMPLE_LVGL_TASK_MIN_DELAY_MS;
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
}

/* Display flushing */
static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    int w = (area->x2 - area->x1 + 1);
    int h = (area->y2 - area->y1 + 1);

    display.startWrite();                            /* Start new TFT transaction */
    display.setAddrWindow(area->x1, area->y1, w, h); /* set the working window */

    display.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);

    display.endWrite();        /* terminate TFT transaction */
    lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

static void lv_tick_task(void *arg) {
    (void)arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id) {
    uint8_t left_button  = getOptionButton();
    uint8_t right_button = getModeButton();

    switch (id) {
        case 0:
            if (M5.Btn.isPressed()) {
                return true;
            }
            break;
        case 1:
            if (left_button) {
                return true;
            }
            break;

        default:
            break;
    }

    return false;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void) {
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for (i = 0; i < 2; i++) {
        /*Return the pressed button's ID*/
        if (button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

/*Will be called by the library to read the button*/
static void button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if (btn_act >= 0) {
        data->state = LV_INDEV_STATE_PR;
        last_btn    = btn_act;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

void lvgl_init(void) {
    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_WIDTH * 20);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res  = LCD_WIDTH;
    disp_drv.ver_res  = LCD_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv_btn;
    lv_indev_drv_init(&indev_drv_btn);
    indev_drv_btn.type       = LV_INDEV_TYPE_BUTTON;
    indev_drv_btn.read_cb    = button_read;
    lv_indev_t *button_indev = lv_indev_drv_register(&indev_drv_btn);

    /*Assign buttons to points on the screen*/
    static const lv_point_t btn_points[2] = {
        {0, 111}, /*Button 0 -> x:10; y:10*/
        {75, 6},  /*Button 0 -> x:10; y:10*/
    };
    lv_indev_set_button_points(button_indev, btn_points);

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    xGuiSemaphore                                     = xSemaphoreCreateMutex();
    const esp_timer_create_args_t periodic_timer_args = {.callback = &lv_tick_task, .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    xTaskCreate(example_lvgl_port_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY,
                &task_lvgl_handle);
}
