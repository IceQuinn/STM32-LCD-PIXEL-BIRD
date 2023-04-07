/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-06     IP155       the first version
 */
#include "pixel_bird.h"


void pixel_bird_thread(void *parameter)
{
    lcd_init();

    //基础环境背景
    GuiClearAll();

    DrawPipes();    //创建一组管道

    while(1)
    {
        MovePipes();    //移动管道

        GuiUpdateDisplayAll();

        rt_thread_mdelay(1000);
    }
}
