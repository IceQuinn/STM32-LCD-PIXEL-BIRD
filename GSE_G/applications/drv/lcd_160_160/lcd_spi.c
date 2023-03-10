/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-07     IP155       the first version
 */
#include "rtdevice.h"
#include "drv_common.h"
#include "drv_spi.h"

#include "lcd_spi.h"
#include "lcd_gpio_api.h"

struct rt_spi_device *spi_dev_lcd;     /* LCD 设备句柄 */


/* 将显示屏挂载到SPI2上 */
int lcd_spi_init(void)
{
    rt_err_t res;

    /* 设置片选管脚模式为输出 */
    rt_pin_mode(LCD_CS, PIN_MODE_OUTPUT);
    /* 把spi20挂到spi2上 */
    res = rt_hw_spi_device_attach(LCD_SPI_BUS_NAME, LCD_SPI_NAME, LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN);
    if (res == RT_EOK)
    {
        rt_kprintf("spi2 bus attach LCD device OK !\r\n");
    }
    spi_dev_lcd = (struct rt_spi_device *)rt_device_find(LCD_SPI_NAME);
    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
        cfg.max_hz = 20 * 1000 *1000; /* 20M,SPI max 42MHz,ssd1351 4-wire spi */

        rt_spi_configure(spi_dev_lcd, &cfg);
    }

    return RT_EOK;

}
/* 导出到自动初始化 */
//INIT_COMPONENT_EXPORT(lcd_spi_init);

rt_size_t lcd_spi_write(void *buf, rt_size_t len)
{
    rt_size_t res = 0;
    res = rt_spi_send(spi_dev_lcd, buf, len);
    return res;
}
