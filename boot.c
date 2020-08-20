/*
 * A simple user interface for this project
 *
 * Copyright 2020 Creep_er
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#include <stdarg.h>
#include "regspinctrl.h"
#include "regslcdif.h"
#include "regsdigctl.h"
#include "regsuartdbg.h"
#include "regsapbh.h"
#include "regsclkctrl.h"
#include "regsicoll.h"
#include "mmu.h"
#include "uart_debug.h"
#include "utils.h"
#include "display.h"
#include "keyboard.h"
#include "exception.h"
#include "irq.h"
#include "hw_irq.h"
#include "memory.h"
#include "console.h"
#include "nand.h"
#include "timer.h"
#include "flash_mapping.h"
#include "./filesystem/fatfs/ff.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


extern int main();
extern void fs_test_main();

void _boot()
{
	disable_interrupts();					//关闭所有中断
	switch_mode(SVC_MODE);					//切换到系统管理模式
	asm volatile ("ldr sp,=#0x0007F000");	//设置系统管理模式下的栈地址
	exception_init();						//初始化异常向量
	irq_init();								//初始化中断
	DFLTP_init();							//初始化页表
	enable_mmu();							//开启内存映射
	stack_init();							//栈初始化（设定异常、系统、中断等模式下的堆栈
	enable_interrupts();					//打开中断

	LCD_init();								//屏幕初始化
	keyboard_init();						//键盘初始化
	LCD_set_contrast(0x40);					//设置对比度
	
	LCD_clear_buffer();						//清屏缓存
	LCD_dma_flush_auto_buffer_start();		//开启自动刷屏
	//malloc_init();
	console_init();
	NAND_init();
	
	
	BF_CS1(UARTDBGIBRD,BAUD_DIVINT,1);
	BF_CS1(UARTDBGFBRD,BAUD_DIVFRAC,36);
	BF_CS1(UARTDBGLCR_H,FEN,1);	
	
	

	
	
	
	Flash_mapping_init();
	
	//fs_test_main();
	
	
	//main();
 
	printf("System halt.");
	fflush(stdout);
	
	while(1)
		{
			
		//	uartdbg_printf("test \n");
		}
}

