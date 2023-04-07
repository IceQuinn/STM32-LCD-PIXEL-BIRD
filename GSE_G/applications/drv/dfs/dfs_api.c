/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-10     IP155       the first version
 */
#include "dfs_api.h"
#include "dfs_fs.h"

void dfs_mount_flash(void)
{
    //
    if(dfs_mount("W25Q64", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("spi flash mount to /\n");
    }
    else
    {
        rt_kprintf("spi flash mount to / failed\n");
    }
}
