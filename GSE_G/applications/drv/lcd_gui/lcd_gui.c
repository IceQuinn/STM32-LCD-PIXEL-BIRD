/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-07     IP155       the first version
 */
#include "lcd_gui.h"
#include "lcd_gpio.h"
#include "lcd_gpio_api.h"


/*
 * 简述显示流程
 * 1、使用画点接口将需要绘画的内容存入 <lkdGuiBuff>缓冲区中，此时显示屏还不能显示你现在绘画的内容
 * 2、使用display接口将绘画的内容一次性刷到显示屏上
 *  */


static uint8_t  lkdGuiBuff[GUIYMAX][GUIXMAX/8 + GUIXMAX%8] = {0};

/* 行位获取数组 */
const static uint8_t colBit[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

/**
  *@brief 向缓冲区画点
  *@param  x,y 坐标
  *@param  color 颜色 <目前只有黑:CBLACK 白:CWHITLE>
  *@retval None
  */
void GuiDrawPoint(uint16_t x, uint16_t y, COLOURS color)
{
    if((x < GUIXMAX) && (y < GUIYMAX))
    {
        if(WHITLE == color)//白色
        {
            lkdGuiBuff[GUIYMAX - 1 - y][(GUIXMAX - 1 - x) >> 3] &= ~colBit[(159-x) & 0x07];
        }
        else if(BLACK == color)//黑色
        {
            lkdGuiBuff[GUIYMAX - 1 - y][(GUIXMAX - 1 - x) >> 3] |= colBit[(159-x) & 0x07];
        }
    }
}

//获取像素点颜色
COLOURS GuiGetPoint(uint16_t x, uint16_t y)
{
    if(lkdGuiBuff[GUIYMAX - 1 - y][(GUIXMAX - 1 - x) >> 3] & colBit[(159-x) & 0x07])
    {
        return BLACK;
    }
    else
    {
        return WHITLE;
    }
}

/**
  *@brief 清除屏幕数据缓存
  */
void GuiClearAll(void)
{
    memset(lkdGuiBuff, WHITLE, sizeof(lkdGuiBuff));
}

/**
  *@brief 将Gui缓冲区数据显示到lcd上
  *@param  None
  *@retval None
  */
void GuiUpdateDisplayAll(void)
{
    uint32_t x,y;

    LCD_A0_HIGH();

    setWindowsProgame();
    for(y = 0; y < GUIYMAX; y++)
    {
        for(x = 0;x < 20; x++)
        {
            write_lcd_datas(lkdGuiBuff[y][x]);
        }
        write_lcd_data(0x00);
    }
}

void test_lcd(int argc, char *argv[])
{
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    for (uint16_t i=0; i < 160; ++i)
    {
        for (uint16_t j=0; j < 160; ++j)
        {
            if((x == i) && (y == j))
            {
                GuiDrawPoint(i, j, BLACK);
            }
            else
            {
                GuiDrawPoint(i, j, WHITLE);
            }
        }
    }

    GuiUpdateDisplayAll();
}
MSH_CMD_EXPORT(test_lcd, test_lcd);


