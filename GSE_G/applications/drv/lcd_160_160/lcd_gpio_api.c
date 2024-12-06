/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-06     IP155       the first version
 */
#include <rtdevice.h>

#include "lcd_gpio_api.h"
#include "lcd_spi.h"


/*
 * lcd硬复位
 */
void lcd_reset(void)
{
    rt_pin_write(LCD_RST, PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(LCD_RST, PIN_HIGH);
}

/* lcd引脚初始化
 * 配置A0、CS、RST引脚为输出
 */
void lcd_gpio_init(void)
{
    rt_pin_mode(LCD_A0, PIN_MODE_OUTPUT);   //指令数据
//    rt_pin_mode(LCD_CS, PIN_MODE_OUTPUT);   //片选
    rt_pin_mode(LCD_RST, PIN_MODE_OUTPUT);  //复位
//    rt_pin_mode(LCD_BLK, PIN_MODE_OUTPUT);  //背光


//    rt_pin_write(LCD_BLK, PIN_LOW);

    lcd_reset();
}

/**
  *@brief 写命令
  *@param  cmd 命令
  *@retval None
  */
rt_err_t write_lcd_command(uint8_t cmd)
{
    rt_size_t len;
    LCD_A0_LOW();    /* 命令低电平 */
    len = lcd_spi_write(&cmd, 1);
    if (0 == len)
    {
        rt_kprintf("lcd write_cmd error.\n");

    }
    return len;
}

/**
  *@brief 写数据
  *@param datas 数据
  *@retval None
  */
rt_err_t write_lcd_datas(uint8_t datas)
{
    uint8_t data[4];
    static const uint8_t flg[] = {0x0, 0xf, 0xf0, 0xff};
    static const uint8_t offset[] = {6, 4, 2, 0};
    for(int i=0; i<4; i++)
    {
        data[i] = flg[(datas >> offset[i])&0x3];
    }

    rt_size_t retlen;
    LCD_A0_HIGH();         /* 数据高电平 */
    retlen = lcd_spi_write(data, 4);
    if (retlen != retlen)
    {
        rt_kprintf("ssd1351_write_data error. \n");
    }
    return retlen;
}

rt_err_t write_lcd_data(uint8_t data)
{
    rt_size_t len;
    LCD_A0_HIGH();         /* 数据高电平 */
    len = lcd_spi_write(&data, 1);
    if (len != len)
    {
        rt_kprintf("ssd1351_write_data error. \n");
    }
    return len;
}


