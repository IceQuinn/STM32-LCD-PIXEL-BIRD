/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-06     IP155       the first version
 */
#include <time.h>
#include <drv_common.h>
#include "pixel_bird.h"

#include "lcd_gpio.h"
#include "lcd_gui.h"
#include "pix_bird_bkg.h"

#define MOVE_CNT    2






void pixel_bird_thread(void *parameter)
{
    static uint32_t pixb_thread_cnt = 0;
    lcd_init();

    //清屏
    GuiClearAll();

//    DrawPipes();    //创建一组管道
    srand(time(0));

    DrawBird();

    while(1)
    {
        GuiUpdateDisplayAll();

        rt_thread_mdelay(5);

        pixb_thread_cnt++;


        if(0 == (pixb_thread_cnt % MOVE_CNT))
        {
            DrawFlyBird();
//            MovePipes();    //移动管道
        }

    }
}
