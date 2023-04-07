/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-13     IP155       the first version
 */
#include "rtdevice.h"
#include "drv_spi.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#include "flash_spi.h"
#include "spi_flash_gpio.h"

rt_spi_flash_device_t w25q64;

/* 将W25Q64挂载在spi2上并配置 */
static int rt_hw_w25q64_init(void)
{
    rt_err_t res;

    /* 设置片选管脚模式为输出 */
    rt_pin_mode(W25Q64_CS_PIN, PIN_MODE_OUTPUT);
    /* 把spi20挂到spi2上 */
    res = rt_hw_spi_device_attach(FLASH_SPI_BUS_NAME, FLASH_SPI_NAME, FLASH_CS_GPIO_PORT, LCD_CS_GPIO_PIN);
    if (res == RT_EOK)
    {
        rt_kprintf("spi2 bus attach W25Q64 device OK !\r\n");
    }
    /* 在通用串行驱动中查找W25Q64设备 */
    w25q64 = rt_sfud_flash_probe("W25Q64", FLASH_SPI_NAME);
    if (RT_NULL == w25q64)
    {
        rt_kprintf("dev w25q64 find error !\r\n");
        return -RT_ERROR;
    };
    return RT_EOK;

}
/* 导出到自动初始化 */
INIT_COMPONENT_EXPORT(rt_hw_w25q64_init);
