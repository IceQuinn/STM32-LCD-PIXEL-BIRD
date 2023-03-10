/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-06     IP155       the first version
 */
#include "lcd_gpio.h"
#include "lcd_gpio_api.h"
#include "lcd_spi.h"

/*
 *  LCD_CS：片选引脚，低有效
 *  LCD_A0：指令或数据，指令：低电平；数据：高电平
 *  LCD_RST：硬复位引脚
 *  LCD_CLK：SPI时钟引脚
 *  LCD_MOSI：SPI数据(指令)引脚
 *
 *  LCD_BLK：背光灯
 *  */




void lcd_init(void)
{
    lcd_spi_init();

    lcd_gpio_init();

    delay_ms(500);

    write_lcd_command(0xB8);     //disable MTP
    write_lcd_command(0x00);
    delay_ms(100);

    write_lcd_command(0xE2);     //system reset
    delay_ms(200);

    write_lcd_command(0xeb);    //set bias=12 这个需要根据你们具体的bias来更改
    write_lcd_command(0x81);    //set vop
    write_lcd_command(90);     //set vop=16.5v（72）, 15.8V（46）16.3V(64)这个参数需要根据你们的VOP来更改
    write_lcd_command(0x2b);    //set internal pump control


    write_lcd_command(0xc4);     //set lcd mapping  control

    write_lcd_command(0x89);     //set ram address control      //原始数据


    //write_lcd_command(0xc2);     //set lcd mapping  control       //修改数据
    //write_lcd_command(0x8d);     //set ram address control


    write_lcd_command(0x24);    // set TC=-0.00%
    write_lcd_command(0xa2);    // set line rate

    write_lcd_command(0xf1);    //set com end
    write_lcd_command(159);



    write_lcd_command(0x85);    //set partical display enable
    write_lcd_command(0xf2);    //set partical display start
    write_lcd_command(0);
    write_lcd_command(0xf3);    //set partical display end
    write_lcd_command(159);

    write_lcd_command(0x40);    //set scorll line
    write_lcd_command(0x50);    //set scroll line

    write_lcd_command(0xd1);    //set color pattern
    write_lcd_command(0xd5);    //set color mode 64k
    write_lcd_command(0xC8);    //set n-line inversion
    write_lcd_command(0x1a);
    write_lcd_command(0xd8);    //set com scan function

    write_lcd_command(0xAD);    //set display enable
}

void setWindowsProgame(void)
{
    write_lcd_command(0x70);  //行地址0
    write_lcd_command(0x60);
    write_lcd_command(0x12);  //列地址35
    write_lcd_command(0x03);

    write_lcd_command(0xf4);
    write_lcd_command(35);//start  col        左边界35
    write_lcd_command(0xf6);
    write_lcd_command(88);//end  col          右边界88
    write_lcd_command(0xf5);
    write_lcd_command(0);//start row          上边界0
    write_lcd_command(0xf7);
    write_lcd_command(159);//end row          下边界159
    write_lcd_command(0xf8);  //窗口功能开
}


