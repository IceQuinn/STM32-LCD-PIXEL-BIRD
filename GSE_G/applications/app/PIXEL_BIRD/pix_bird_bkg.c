/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-06     IP155       the first version
 */
#include "pix_bird_bkg.h"

#include "lcd_gui.h"
#include "lcd_gpio_api.h"

// 定义空管道的高度
#define PIPE_HEIGHT 50

// 定义管道的宽度
#define PIPE_WIDTH 10

// 定义每个管道之间的空隙大小
#define PIPE_GAP 25

// 绘制一个管道
void DrawPipe(unsigned int x, unsigned int gap_y)
{
    // 绘制上方管道
    for (unsigned int i = 0; i < gap_y; i++)
    {
        for (unsigned int j = 0; j < PIPE_WIDTH; j++)
        {
            GuiDrawPoint(x + j, i, 1); // 绘制黑色像素
        }
    }

    // 绘制下方管道
    for (unsigned int i = gap_y + PIPE_HEIGHT; i < 160; i++)
    {
        for (unsigned int j = 0; j < PIPE_WIDTH; j++)
        {
            GuiDrawPoint(x + j, i, 1); // 绘制黑色像素
        }
    }
}

// 绘制一组管道
void DrawPipes(void)
{
    unsigned int x = 0; // 管道的起始横坐标
    unsigned int gap_y; // 上下管道的间隙起始纵坐标

    while (x < 160)
    {
        gap_y = rand() % (160 - PIPE_HEIGHT - 2 * PIPE_GAP) + PIPE_GAP; // 随机生成上下管道之间的间隙
        DrawPipe(x, gap_y); // 绘制管道
        x += PIPE_WIDTH + PIPE_GAP; // 计算下一个管道的起始横坐标
    }
}

// 定义一个函数来移动这组管道
void MovePipes(void)
{
    for (uint16_t m_x=0; m_x < GUIXMAX-1; ++m_x)
    {
        for (uint16_t m_y=0; m_y < GUIYMAX; ++m_y)
        {
            uint8_t color = GuiGetPoint(m_x+1, m_y);    //获取下一列像素
            GuiDrawPoint(m_x, m_y, color);              //补到本列像素
        }
    }
}
