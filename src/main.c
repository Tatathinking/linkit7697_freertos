/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* hal includes */
#include "hal.h"
#include "system_mt7687.h"
#include "top.h"

#include <cmsis_os.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the HAL_UART_0 one at a time */
    hal_uart_put_char(HAL_UART_0, ch);
    return ch;
}

/**
*@brief Configure and initialize UART hardware initialization for logging.
*@param None.
*@return None.
*/
static void plain_log_uart_init(void)
{
    hal_uart_config_t uart_config;

    /* gpio config for uart0 */
    hal_gpio_init(HAL_GPIO_2);
    hal_gpio_init(HAL_GPIO_3);
    hal_pinmux_set_function(HAL_GPIO_2, HAL_GPIO_2_UART1_RX_CM4);
    hal_pinmux_set_function(HAL_GPIO_3, HAL_GPIO_3_UART1_TX_CM4);

    /* COM port settings */
    uart_config.baudrate = HAL_UART_BAUDRATE_115200;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.parity = HAL_UART_PARITY_NONE;
    hal_uart_init(HAL_UART_0, &uart_config);
}

/**
*@brief Configure and initialize the systerm clock.
*@param None.
*@return None.
*/
static void SystemClock_Config(void)
{
    top_xtal_init();
}

/**
*@brief  Initialize the periperal driver in this function. In this example, we initialize UART, Flash, and NVIC drivers.
*@param None.
*@return None.
*/
static void prvSetupHardware(void)
{
    /* Peripherals initialization */
    plain_log_uart_init();
}

#if 0

void this_gpio_init(void){

    hal_gpio_data_t data_pull_up;
    hal_gpio_data_t data_pull_down;
    hal_gpio_status_t ret;
    hal_pinmux_status_t ret_pinmux_status;

    OneWire_Reset();

    //PIN
    ret = hal_gpio_init(HAL_GPIO_31);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_init failed\r\n");
        hal_gpio_deinit(HAL_GPIO_31);
        return;
    }
    printf("hal_gpio_init() -- passed \r\n");

    /* Set pin as GPIO mode.*/
    ret_pinmux_status = hal_pinmux_set_function(HAL_GPIO_31, HAL_GPIO_31_GPIO31);
    if (HAL_PINMUX_STATUS_OK != ret_pinmux_status) {
        printf("hal_pinmux_set_function failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }
    printf("hal_pinmux_set_function() -- passed \r\n");

    /* Set GPIO as output.*/
    ret = hal_gpio_set_direction(HAL_GPIO_31, HAL_GPIO_DIRECTION_OUTPUT);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_set_direction failed\r\n");
        hal_gpio_deinit(HAL_GPIO_31);
        return;
    }
    printf("hal_gpio_set_direction() -- passed \r\n");

    /* Configure the pull state to No_pull. */
    ret = hal_gpio_disable_pull(HAL_GPIO_31);
    if (HAL_GPIO_STATUS_OK != ret) {
        printf("hal_gpio_disable_pull failed\r\n");
        hal_gpio_deinit(HAL_GPIO_33);
        return;
    }
    printf("hal_gpio_disable_pull() -- passed \r\n");
}
#endif

osThreadId 	Ds18b20Handle;
void Task_Ds18b20(void const * argument);

void	Ds18b20_Init(osPriority Priority)
{
	osThreadDef(myTask_Ds18b20, Task_Ds18b20, Priority, 0, 128);
    Ds18b20Handle = osThreadCreate(osThread(myTask_Ds18b20), NULL);	
}

void Task_Ds18b20(void const * argument)
{
    for(;;){
    /* Add your application code here */
    printf("\r\n\r\n");
    /* The output UART used by printf is set by plain_log_uart_init() */
    printf("welcome to main() temp \r\n");
    printf("\r\n\r\n");
    printf("starting sensing temp \r\n");
    osDelay(3000);
    }
}

int main(void)
{
    /* Configure system clock */
    SystemClock_Config();

    /* Configure the hardware */
    prvSetupHardware();

    /* Enable I,F bits */
    __enable_irq();
    __enable_fault_irq();

    Ds18b20_Init(osPriorityRealtime);
    //this_gpio_init();
    //osKernelInitialize();

    osKernelStart();
    while (1);
}

