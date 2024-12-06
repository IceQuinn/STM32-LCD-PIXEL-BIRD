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

#include "at32f403a_407.h"
#include "lcd_gpio.h"
#include "pixel_bird.h"
#include "user_common.h"
#include "btn_chk.h"
#include "blk_mgmt.h"

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
        {"btn",         Btn_Thread,         RT_NULL,    1024,   20, 15},    /* 计量线程 */
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


void at32_drv_common(void)
{
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    gpio_pin_remap_config(SWJTAG_GMUX_010, TRUE);    /*!< jtag-dp disabled and sw-dp enabled */
//    gpio_pin_remap_config(SPI3_GMUX_0010, TRUE);
}

void wk_periph_clock_config(void)
{
  /* enable iomux periph clock */
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

  /* enable gpioa periph clock */
//  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* enable gpiod periph clock */
  crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);

  /* enable tmr2 periph clock */
  crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
}

void wk_debug_config(void)
{
  /* jtag-dp disabled and sw-dp enabled */
  gpio_pin_remap_config(SWJTAG_GMUX_010, TRUE);
}

void wk_nvic_config(void)
{
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
}

#define TICK_COUNT_MAX                   (uint32_t)(0xFFFFFF)
#define TICK_COUNT_VALUE                 (SysTick->VAL)
volatile uint32_t ticks_count_us;
__WEAK void wk_timebase_init(void)
{
  crm_clocks_freq_type crm_clocks;
  uint32_t frequency = 0;

  /* get crm_clocks */
  crm_clocks_freq_get(&crm_clocks);

  frequency = crm_clocks.ahb_freq / 8;

  /* config systick clock source */
  systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_DIV8);
  ticks_count_us = (frequency / 1000000U);
  /* system tick config */
  TICK_COUNT_VALUE = 0UL;
  SysTick->LOAD = TICK_COUNT_MAX;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

int main(void)
{
    int count = 1;

    wk_periph_clock_config();

    wk_debug_config();

//    wk_nvic_config();

//    wk_timebase_init();
//
//    dfs_mount_flash();

    BLK_Init();

    user_thread_init();

    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
