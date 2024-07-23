/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef _LVGL_PORTING_H_
#define _LVGL_PORTING_H_

#include <lvgl.h>

#include "main.h"
#include "app_lvgl.h"

void lvgl_init(void);
bool example_lvgl_lock(int timeout_ms);
void example_lvgl_unlock(void);

extern TaskHandle_t task_lvgl_handle;

#endif
