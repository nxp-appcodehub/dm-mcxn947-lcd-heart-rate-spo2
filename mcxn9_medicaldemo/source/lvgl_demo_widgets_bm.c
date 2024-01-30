/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "lvgl_support.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"
#include "flexio_8080_drv.h"
#include "lcd_drv.h"
#include "fsl_inputmux.h"
#include "string.h"
#include "fsl_lpi2c.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "fsl_gt911.h"
#include "gui_guider.h"
#include "events_init.h"

#include "spo2.h"
#include "spo2.h"
#include "hr_sensor.h"
#include "hr_sensor.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lpi2c.h"
#include "fsl_lpuart.h"


volatile static bool g_enable_to_update = false;


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 1 ms per tick. */
#ifndef LVGL_TICK_MS
#define LVGL_TICK_MS 1U
#endif

/* lv_task_handler is called every 5-tick. */
#ifndef LVGL_TASK_PERIOD_TICK
#define LVGL_TASK_PERIOD_TICK 5U
#endif   
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
typedef struct _QEI_Para{
	uint32_t *coprocessor_stack;
	uint32_t *p_camera_buffer;
	uint32_t *p_AI_buffer;
	uint32_t *p_coord_index;
} QEI_Para;

#define ARRRAY_LONG 20
#define CHECKTIME 6
#define SPO2LIMIT 290
static void DEMO_SetupTick(void);
static volatile uint32_t s_tick        = 0U;
static volatile bool s_lvglTaskPending = false;
/*******************************************************************************
 * Variables
 ******************************************************************************/
lv_ui guider_ui;
const char graff[ARRRAY_LONG]={1,3,5,7,9,22,50,70,90.100,100,90,70.40,30,10, 15 ,18 ,20 ,20};
uint8_t indice = 0;
uint8_t text_spo[2];
uint8_t text_hr[3];

uint16_t wait = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/
void chart_task(uint8_t hr, uint8_t spo);
void chart_hr(void);
void update_spolabel(uint16_t spo, uint8_t hr);
/*!
 * @brief Main function
 */


int main(void)
{
    /* attach FRO 12M to FLEXCOMM4 (debug console) */
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

	/* Init I2C2 for Touch, LCD, PMIC*/
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
	CLOCK_EnableClock(kCLOCK_LPFlexComm2);
	CLOCK_EnableClock(kCLOCK_LPI2c2);
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 0u );
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u );

	SYSCON->LPCAC_CTRL &= ~1;   // rocky: enable LPCAC ICache
	SYSCON->NVM_CTRL &= SYSCON->NVM_CTRL & ~(1<<2|1<<4); // enable flash Data cache

	BOARD_InitPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
	init_hrsensor();
	PRINTF("Sensor inited\r\n");


	/* Init FlexIO for this demo. */
	Demo_FLEXIO_8080_Init();
	/* TFT PROTO 5" Capacitive(MIKROE-2406)  */
#ifdef LCD_SSD1963  
	LCD_SSD1963_Init();
#endif    

#ifdef LCD_ST7796S_TFT
	LCD_ST7796S_TFT_Init();
#endif  

	/*NXP low cost LCD module*/
#ifdef LCD_ST7796S_IPS
	LCD_ST7796S_IPS_Init();
#endif

	DEMO_SetupTick();
	lv_init();
	lv_port_disp_init();
	//lv_port_indev_init();
	//lv_demo_widgets();
	setup_ui(&guider_ui);
	PRINTF("lvgl bare metal widgets demo\r\n");
	for (;;)
	{

		while (!s_lvglTaskPending)
		{
		}
		s_lvglTaskPending = false;



		if(true == g_enable_to_update)
		{
			update_spo2();
			/*Read for erase interrupt flags*/
			read_interrupt_flags(0xFF, interrupt_register_2);
			read_interrupt_flags(0xFF, interrupt_register_1);

			uint16_t spo2       =  hr_get_adc_ir_ultra_filttered();
			uint16_t spo2_sat 	=  spo2_get_spo2_in_blood();
			uint8_t heart_rate  =  spo2_get_heart_rate();


			if(wait == CHECKTIME){

				if(spo2 > SPO2LIMIT){

					PRINTF("Sensor value: %d\r\n", spo2 );

				}else{

					chart_task(heart_rate, (uint8_t)spo2);
					chart_hr();
					update_spolabel(spo2_sat, heart_rate);

				}

				wait=0;
			}

			g_enable_to_update = false;
			wait++;

			if(spo2 != 0 && spo2 > SPO2LIMIT){

				lv_obj_set_style_opa(guider_ui.screen_warning_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

			}else{

				lv_obj_set_style_opa(guider_ui.screen_warning_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

			}

		}else{

			 lv_obj_set_style_opa(guider_ui.screen_warning_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

		}



         lv_task_handler();



	}
}
void update_spolabel(uint16_t spo, uint8_t hr)
{

	if(spo >= 99){

		lv_label_set_text(guider_ui.screen_lab_spo2_value,  "99");

	} else {

	text_spo[0] = spo / 10;
	text_spo[1] = spo % 10;
	//text_spo[1] = spo - ((spo / 10) * 10);

	text_spo[0] = 	text_spo[0] + '0';
	text_spo[1] = 	text_spo[1] + '0';
	lv_label_set_text(guider_ui.screen_lab_spo2_value,  text_spo);
	}

	text_hr[0] = 0;
			text_hr[1] =  0;
					text_hr[2] = 0;
if(hr >= 100){

	text_hr[0] = hr / 100;
	hr = hr - ((hr / 100) * 100);
	text_hr[1] = hr /10;

	text_hr[2] = hr % 10;
	//hr = hr - ((hr / 10) * 10);
	//text_hr[2] = hr;

	text_hr[0] = text_hr[0]  + '0';
	text_hr[1] = text_hr[1]  + '0';
	text_hr[2] = text_hr[2]  + '0';
}else{

	text_hr[0] = hr /10;
	text_hr[1] = hr % 10;

	//hr = hr - ((hr / 10) * 10);
	//text_hr[1] = hr;

	text_hr[0] = text_hr[0]  + '0';
	text_hr[1] = text_hr[1]  + '0';

}




	lv_label_set_text(guider_ui.screen_lab_bpm_value,  text_hr);


}
void chart_hr(void)
{


	 lv_chart_set_next_value(guider_ui.chart_one, guider_ui.ser_one, graff[indice]);       /*set point_one to next*/

	 if(indice == ARRRAY_LONG - 1){

		 indice=0;

	 } else {

		 indice++;

	 }

}
void chart_task(uint8_t hr, uint8_t spo)
{
	 lv_chart_set_next_value(guider_ui.chart_two, guider_ui.ser_two, spo);
}

static void DEMO_SetupTick(void)
{
	if (0 != SysTick_Config(SystemCoreClock / (LVGL_TICK_MS * 1000U)))
	{
		PRINTF("Tick initialization failed\r\n");
		while (1)
			;
	}
}

void SysTick_Handler(void)
{
	s_tick++;
	lv_tick_inc(LVGL_TICK_MS);

	if ((s_tick % LVGL_TASK_PERIOD_TICK) == 0U)
	{
		s_lvglTaskPending = true;
	}
}

void GPIO50_IRQHandler(void)
{
	g_enable_to_update = true;
	GPIO_PinClearInterruptFlag(GPIO_INTERRUPT, PIN_INTERRUPT);

}


