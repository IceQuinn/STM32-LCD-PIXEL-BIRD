/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-07     IP155       the first version
 */
#ifndef APPLICATIONS_DRV_LCD_160_160_LCD_SPI_H_
#define APPLICATIONS_DRV_LCD_160_160_LCD_SPI_H_


/* 显示屏 */
#define     LCD_SPI_BUS_NAME        "spi2"
#define     LCD_SPI_NAME            "spi21"

int lcd_spi_init(void);

rt_size_t lcd_spi_write(void *buf, rt_size_t len);

#endif /* APPLICATIONS_DRV_LCD_160_160_LCD_SPI_H_ */
