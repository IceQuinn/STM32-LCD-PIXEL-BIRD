/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-13     IP155       the first version
 */
#ifndef APPLICATIONS_DRV_SPI_FLASH_SPI_FLASH_GPIO_H_
#define APPLICATIONS_DRV_SPI_FLASH_SPI_FLASH_GPIO_H_

#include <rtdevice.h>
#include "drv_common.h"

#define     FLASH_CS_GPIO_PORT  GPIOB
#define     LCD_CS_GPIO_PIN     GPIO_PINS_12
#define     W25Q64_CS_PIN       GET_PIN(B, 12)

#endif /* APPLICATIONS_DRV_SPI_FLASH_SPI_FLASH_GPIO_H_ */
