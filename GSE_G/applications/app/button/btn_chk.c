/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-01     mutou       the first version
 */
#include "btn_chk.h"
#include "user_common.h"
#include <drv_common.h>
#include <rtdevice.h>

#include "btn_gpio.h"

#define BTN_ESC     GET_PIN(B, 1)
#define BTN_UP      GET_PIN(B, 0)
#define BTN_DOWN    GET_PIN(A, 1)
#define BTN_ENTER   GET_PIN(A, 0)

#define Btn_Read(x)     rt_pin_read(x)

struct Btn_In_Sta_Str
{
    uint16_t real_sta;  // 实时状态
    uint16_t clik_cnt;  // 保持时间计数
    uint16_t sta;
};

struct Btn_Cfg_Str
{
    uint16_t pin;
    uint16_t level;     // 有效电平
    uint16_t delay;
    struct Btn_In_Sta_Str Btn_In_Sta;
    void (*btn_cb)(uint16_t pin);
};

struct Btn_Cfg_Str Btn_Cfg[] =
{
    {BTN_ESC,   RESET, 2, {0}, RT_NULL},
    {BTN_UP,    RESET, 2, {0}, RT_NULL},
    {BTN_DOWN,  RESET, 2, {0}, RT_NULL},
    {BTN_ENTER, RESET, 2, {0}, RT_NULL},
};


void btn_clik_cb(uint16_t pin)
{
    if (BTN_ESC == pin)
    {
        rt_kprintf("Button Clik:BTN_ESC\n");
    }
    else if(BTN_UP == pin)
    {
        rt_kprintf("Button Clik:BTN_UP\n");
    }
    else if(BTN_DOWN == pin)
    {
        rt_kprintf("Button Clik:BTN_DOWN\n");
    }
    else if(BTN_ENTER == pin)
    {
        rt_kprintf("Button Clik:BTN_ENTER\n");
    }
}

void Btn_Init(void)
{
    for (int i = 0; i <countof(Btn_Cfg) ; ++i)
    {
        Btn_GPIO_Init(Btn_Cfg[i].pin);
        Btn_Cfg[i].btn_cb = btn_clik_cb;
    }


}

void Btn_Check(void)
{
    uint16_t read_pin = 0;
    uint8_t  real_sta = 0;
    for (int i = 0; i < countof(Btn_Cfg); ++i)
    {
        read_pin = Btn_Cfg[i].pin;
        real_sta = Btn_Read(read_pin);
        if(Btn_Cfg[i].Btn_In_Sta.sta != real_sta)
        {
            Btn_Cfg[i].Btn_In_Sta.clik_cnt++;
            if(Btn_Cfg[i].delay == Btn_Cfg[i].Btn_In_Sta.clik_cnt)
            {
                Btn_Cfg[i].Btn_In_Sta.sta = real_sta;
                if(Btn_Cfg[i].level == Btn_Cfg[i].Btn_In_Sta.sta)
                {
                    Btn_Cfg[i].btn_cb(read_pin);
                }
                Btn_Cfg[i].Btn_In_Sta.clik_cnt = 0;
            }
        }
        else
        {
            Btn_Cfg[i].Btn_In_Sta.clik_cnt = 0;
        }
    }
}


void Btn_Thread(void *p)
{
    Btn_Init();

    while(1)
    {
        Btn_Check();
        rt_thread_mdelay(5);
    }
}
