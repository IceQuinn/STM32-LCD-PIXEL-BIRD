/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-07     IP155       the first version
 */
#include "drv_common.h"
#include <stdint.h>
#include "pix_bird_bird.h"

#include "lcd_gui.h"

#define PIXEL_BIRD_X    20
#define PIXEL_BIRD_Y    80

// 定义像素鸟的身体部分坐标
#define  BODY_SIZE  20  // 鸟身体大小为14x14像素（包含填充）

struct pixel_bird_sta
{
    int16_t speed;      //速度
    int16_t acc;        //加速度
    uint16_t gravity;   //重力
};

// 定义像素鸟的每个像素点的坐标
int pixel_bird[BODY_SIZE][BODY_SIZE] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,1,0,0,1},
        {0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,1,0,1},

        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}
};

void draw_bird(uint16_t base_x, uint16_t base_y)
{
    static uint16_t last_base_x = PIXEL_BIRD_X;
    static uint16_t last_base_y = PIXEL_BIRD_Y;

    if((last_base_x != base_x) || (last_base_y != base_y))
    {
        //像素鸟的位置移动了，清空原位置的像素点
        for (uint16_t x=0; x < BODY_SIZE; ++x)
        {
            for (uint16_t y=0; y < BODY_SIZE; ++y)
            {
                GuiDrawPoint(last_base_x+x, last_base_y+y, WHITLE);
            }
        }
        last_base_x = base_x;
        last_base_y = base_y;
    }

    for (uint16_t x=0; x < BODY_SIZE; ++x)
    {
        for (uint16_t y=0; y < BODY_SIZE; ++y)
        {
            //绘制像素鸟
            GuiDrawPoint(base_x+x, base_y+y, pixel_bird[x][y]);

        }
    }
}

void DrawBird(void)
{
    draw_bird(20, 80);
}

struct pixel_bird_sta pixel_bird_stas = {0, -1, 1};
void DrawFlyBird(void)
{
    static uint16_t x = 20;
    static uint16_t y = 80;
    draw_bird(x, y);
    pixel_bird_stas.speed += pixel_bird_stas.acc;
    y -= pixel_bird_stas.speed;
}


void btn_clik_esc_cb(void)
{

}
void btn_clik_up_cb(void)
{
    pixel_bird_stas.speed = 8;
}
void btn_clik_down_cb(void)
{

}
void btn_clik_entry_cb(void)
{

}

void change_speed(void)
{
    pixel_bird_stas.speed = 8;
}
MSH_CMD_EXPORT(change_speed, change_speed);



