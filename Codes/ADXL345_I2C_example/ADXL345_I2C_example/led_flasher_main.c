/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
/*
  simple code to read ADXL343/344/345 Sensor I2C Mode
  written by : Mohannad Rawashdeh
  
*/
#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>
#include "ADXL345/ADXL34x.h"
struct Acc_adxl34x_t adxl345;

void  config_adxl_IRQ();

void  config_adxl_IRQ()
{
	adxl34x_get_Interrupt_Status(&adxl345);
	/*clear older irq map for the first time (if necessary based on your application)*/
	for (int8_t i=0;i<8;i++)
	{
		adxl34x_set_mapInterrupt(&adxl345,ADXL34x_IRQ1,i);
	}
	/*enable both irq_src_data_ready for IRQ0 & single tap for IRQ1*/
	adxl345.IRQ_source = irq_src_data_ready + irq_src_single_tap;
	
	adxl34x_enableInterrupt(&adxl345);
	
	adxl34x_set_mapInterrupt(&adxl345,ADXL34x_IRQ1,irq_map_data_ready);
	adxl34x_set_mapInterrupt(&adxl345,ADXL34x_IRQ2,irq_map_single_tap);
	delay_ms(100);
	printf("irq map %d\r\n",adxl34x_get_mapInterrupt(&adxl345));
}
int main(void)
{
	atmel_start_init();
	i2c_m_sync_set_slaveaddr(&I2C_ADXL345, ADXL34x_ADDRESS, I2C_M_SEVEN);
	i2c_m_sync_enable(&I2C_ADXL345);
	printf("\r\nStart ADXL345 Test\r\n");
	uint8_t checkinit= adxl34x_init(&adxl345);
	if (checkinit != adxl_error_non)
	{
		printf("*** error initi ! ****\r\n");
	}
	/*enable this line if you want to enable IRQ functionality*/
	 config_adxl_IRQ();
	/*set the data range and  data rate adxl34x_set_Range*/
	adxl34x_set_DataRate(&adxl345,ADXL34x_DATARATE_100_HZ);
	delay_ms(10);
	adxl34x_set_Range(&adxl345,ADXL343_RANGE_16_G);
	delay_ms(100);
	uint8_t getRange=adxl34x_get_Range(&adxl345);
	delay_ms(10);
	uint8_t dataRate=adxl34x_get_DataRate(&adxl345);	
	printf("range: 0x%02X    Rate: 0x%0X \r\n",getRange,dataRate);
	//adxl34x_set_axisOffset(&adxl345,-5,-2,3);
	printf("Run zero offset test ... please wait\r\n");
	adxl34x_set_zeroOffset(&adxl345);
	delay_ms(2000);
	//adxl34x_set_axisOffset(&adxl345,-1,0,0);
	while (true) 
	{
		adxl34x_refresh_xyz(&adxl345);
		adxl34x_get_axisOffset(&adxl345);
		printf("raw_x= %03d		raw_y= %03d		raw_z= %03d\r\n",adxl345.raw_x,adxl345.raw_y,adxl345.raw_z);
		printf("x: %2.4f		y: %2.4f		z: %2.4f \r\n",adxl345.x_axis,adxl345.y_axis,adxl345.z_axis);
		printf("offset x=%d		offset_y=%d			 offset_z=%d\r\n",adxl345.offset_x_axis,adxl345.offset_y_axis,adxl345.offset_z_axis);
		delay_ms(500);
		gpio_toggle_pin_level(LED0);
	}
}
