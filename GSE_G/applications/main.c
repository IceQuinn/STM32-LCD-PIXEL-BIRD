/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-06     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "lcd_gpio.h"
#include "pixel_bird.h"
#include "user_common.h"

/* 线程结构体 */
typedef struct
{
    char        *name;                                  /**< the name of thread */
    void        (*entry)(void *parameter);              /**entry the entry function of thread*/
    void        *parameter;                             /**parameter the parameter of thread enter function*/
    rt_uint32_t stack_size;                             /**stack_size the size of thread stack*/
    rt_uint8_t  priority;                               /**priority the priority of thread*/
    rt_uint32_t tick;                                   /**tick the time slice if there are same priority thread*/
}user_thread_table_typedef;

const user_thread_table_typedef user_thread_table[] = {
        {"px_bird",     pixel_bird_thread,  RT_NULL,    1024,   17, 15},    /* 计量线程 */
};

void user_thread_init(void)
{
    rt_thread_t tid1 = RT_NULL;
    for(uint16_t i=0; i<countof(user_thread_table); i++)
    {
        tid1 = rt_thread_create(user_thread_table[i].name,
                user_thread_table[i].entry,
                user_thread_table[i].parameter,
                user_thread_table[i].stack_size,
                user_thread_table[i].priority,
                user_thread_table[i].tick);
        if (tid1 != RT_NULL)
        {
            rt_thread_startup(tid1);
        }
        else
        {
            LOG_E("%s thread create fail", user_thread_table[i].name);
        }
    }
}

int main(void)
{
    int count = 1;

    dfs_mount_flash();

    user_thread_init();

    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
