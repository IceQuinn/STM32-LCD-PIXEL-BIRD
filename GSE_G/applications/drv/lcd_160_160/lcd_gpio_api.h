/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-06     IP155       the first version
 */
#ifndef APPLICATIONS_DRV_LCD_160_160_LCD_GPIO_API_H_
#define APPLICATIONS_DRV_LCD_160_160_LCD_GPIO_API_H_

#include <rtdevice.h>
#include "drv_common.h"

#define  GUIXMAX    160
#define  GUIYMAX    160

#define     LCD_A0              GET_PIN(C, 2)
#define     LCD_A0_LOW()        rt_pin_write(LCD_A0, PIN_LOW);
#define     LCD_A0_HIGH()       rt_pin_write(LCD_A0, PIN_HIGH);

#define     LCD_CS_GPIO_PORT    GPIOC
#define     LCD_CS_GPIO_PIN     GPIO_PINS_3
#define     LCD_CS              GET_PIN(C, 3)

#define     LCD_RST             GET_PIN(C, 1)

#define     LCD_BLK             GET_PIN(A, 15)
#define     LCD_BLK_ON()        rt_pin_write(LCD_BLK, PIN_LOW);
#define     LCD_BLK_OFF()       rt_pin_write(LCD_BLK, PIN_HIGH);


#define     delay_ms        rt_thread_mdelay

void lcd_gpio_init(void);

rt_err_t write_lcd_command(uint8_t cmd);

rt_err_t write_lcd_datas(uint8_t datas);
rt_err_t write_lcd_data(uint8_t data);

#endif /* APPLICATIONS_DRV_LCD_160_160_LCD_GPIO_API_H_ */
