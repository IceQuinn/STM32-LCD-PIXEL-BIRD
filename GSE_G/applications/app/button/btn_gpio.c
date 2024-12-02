/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-01     mutou       the first version
 */
#include "btn_gpio.h"
#include <rtdevice.h>






void Btn_GPIO_Init(uint16_t pin)
{
    rt_pin_mode(pin     , PIN_MODE_INPUT);
}


int Get_Btn(uint16_t pin)
{
    return rt_pin_read(pin);
}
