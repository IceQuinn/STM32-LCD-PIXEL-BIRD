/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-07     IP155       the first version
 */
#ifndef APPLICATIONS_DRV_LCD_GUI_LCD_GUI_H_
#define APPLICATIONS_DRV_LCD_GUI_LCD_GUI_H_

#include <stdint.h>

typedef enum COLOUR
{
    WHITLE,
    BLACK,
}COLOURS;

void GuiDrawPoint(uint16_t x, uint16_t y, COLOURS color);

#endif /* APPLICATIONS_DRV_LCD_GUI_LCD_GUI_H_ */
