/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-01     mutou       the first version
 */
#ifndef APPLICATIONS_APP_BUTTON_BTN_GPIO_H_
#define APPLICATIONS_APP_BUTTON_BTN_GPIO_H_

#include <drv_common.h>

void Btn_GPIO_Init(uint16_t pin);

int Get_Btn(uint16_t pin);


#endif /* APPLICATIONS_APP_BUTTON_BTN_GPIO_H_ */
