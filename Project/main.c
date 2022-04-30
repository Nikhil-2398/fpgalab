/*==========================================================
 * Copyright 2020 QuickLogic Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *==========================================================*/

/*==========================================================
 *
 *    File   : main.c
 *    Purpose: main for QuickFeather helloworldsw and LED/UserButton test
 *                                                          
 *=========================================================*/

#include "Fw_global_config.h"   // This defines application specific charactersitics

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"

/*    Include the generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"

#include "cli.h"

#include "LCD16x2.h"
#include "LCD16x2_io.h"
#include "PyHal_GPIO.h"


const char *SOFTWARE_VERSION_STR;


/*
 * Connections
        LCD PIN <----> PYGMY
        LCD_D4  <---->  6
        LCD_D5  <---->  8
        LCD_D6  <---->  10
        LCD_D7  <---->  12
        LCD_RS  <---->  2
        LCD_EN  <---->  4
        LCD_RW  <---->  GND
 */


extern void qf_hardwareSetup();
static void nvic_init(void);

int get_choice(){

int x,y,z;
	while(1)
    {
    	x = PyHal_GPIO_Get(23);
        y = PyHal_GPIO_Get(25);
        z = PyHal_GPIO_Get(27);
    
    	if (x|y|z)
    	{
    	LcdClear();
    	if(x) return 1;
    	if(y) return 2;
    	if(z) return 3;
    	
    	}
    }
}

int main(void)
{

    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_hello-fpga-gpio-ctlr";
    HAL_Delay_Init();
    qf_hardwareSetup();
   nvic_init();

    dbg_str("\n\n");
    dbg_str( "##########################\n");
    dbg_str( "Quicklogic QuickFeather FPGA GPIO CONTROLLER EXAMPLE\n");
    dbg_str( "SW Version: ");
    dbg_str( SOFTWARE_VERSION_STR );
    dbg_str( "\n" );
    dbg_str( __DATE__ " " __TIME__ "\n" );
    dbg_str( "##########################\n\n");

    dbg_str( "\n\nHello HIMANSHU, look at the LCD!!\n\n");	// <<<<<<<<<<<<<<<<<<<<<  Change me!
    
    PyHal_GPIO_Set(18,1);//blue
   
    
    PyHal_GPIO_SetDir(23,0); // MSB : 1
    PyHal_GPIO_SetDir(25,0);
    PyHal_GPIO_SetDir(27,0); // LSB : 3
    
    LcdInit(); 
    dbg_str( "\ninit done\n");

    while(1){
        
        LcdClear();
	HAL_DelayUSec(500*1000);
	int  x = PyHal_GPIO_Get(23);
	int y = PyHal_GPIO_Get(25);
	int z = PyHal_GPIO_Get(27);
    
	    LcdWriteString("list of bev: ");
	    HAL_DelayUSec(1000*2000);
	    LcdClear();
	    LcdWriteString("1. Pepsi     $1.00");
	    HAL_DelayUSec(1000*2000);
	    LcdClear();                          
	    LcdWriteString("2. Coke   $2.00"); 
	    HAL_DelayUSec(1000*2000);
	    LcdClear();                       
	    LcdWriteString("3. Dew  $3.00"); 
	    HAL_DelayUSec(1000*2000);
	    LcdClear();                  

       

    LcdWriteString("Enter your choice: ");
    int choice1, choice2;
    choice1 = get_choice();
    
    switch(choice1){
    	case 1: 
    		LcdWriteString("You choose Pepsi");
              	HAL_DelayUSec(2000*1000);
              	LcdClear();                   
              	LcdWriteString("Enter your money"); 
              	LcdSetAddress(16);
              	LcdWriteString("$5   $10   &15  ");
    		choice2 = get_choice();
    		switch(choice2){
    			case 1:
    				LcdWriteString("Rem. money : 4");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
    			
    				break;
    			case 2:
    				LcdWriteString("Rem. money : 9");
			     	HAL_DelayUSec(1000*5000);
			      	LcdClear();
    				break;
    				
    			case 3:
    				LcdWriteString("Rem. money : 14");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
              			break;
              			
    			default : LcdWriteString("returning home");
    				break;
    		}       break;
    		
	    case 2: 
	    
	    	LcdWriteString("You choose Coke");
              	HAL_DelayUSec(2000*1000);
              	LcdClear();                   
              	LcdWriteString("Enter your money"); 
              	LcdSetAddress(16);
              	LcdWriteString("$5   $10   &15  ");
    		choice2 = get_choice();
    		switch(choice2){
    			case 1:
    				LcdWriteString("Rem. money : 3");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
    			
    				break;
    			case 2:
    				LcdWriteString("Rem. money : 8");
			     	HAL_DelayUSec(1000*5000);
			      	LcdClear();
    				break;
    				
    			case 3:
    				LcdWriteString("Rem. money : 13");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
              			break;
              			
    			default : LcdWriteString("returning home");
    				break;
    		}       break;
    		
    		case 3: LcdWriteString("You choose Dew");
              	HAL_DelayUSec(2000*1000);
              	LcdClear();                   
              	LcdWriteString("Enter your money"); 
              	LcdSetAddress(16);
              	LcdWriteString("$5   $10   &15  ");
    		choice2 = get_choice();
    		switch(choice2){
    			case 1:
    				LcdWriteString("Rem. money : 2");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
    			
    				break;
    			case 2:
    				LcdWriteString("Rem. money : 7");
			     	HAL_DelayUSec(1000*5000);
			      	LcdClear();
    				break;
    				
    			case 3:
    				LcdWriteString("Rem. money : 12");
             			HAL_DelayUSec(1000*5000);
              			LcdClear();
              			break;
              			
    			default : LcdWriteString("returning home");
    				break;
    		}       break;
	}
 
    }

    while(1);
}

static void nvic_init(void)
 {
    // To initialize system, this interrupt should be triggered at main.
    // So, we will set its priority just before calling vTaskStartScheduler(), not the time of enabling each irq.
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
 }   

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}

