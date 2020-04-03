/*
 * ADXL34x.c
 *
 * Created: 4/2/2020 2:07:35 AM
 *  Author: Mohannad Rawashdeh
 */ 
#include "ADXL345/ADXL34x.h"
#include "math.h"
/*local get xyz function*/
static int16_t get_x_axis(void)
{
	#if ADXL_I2C_Mode == 1
	return i2c_driver_read16(ADXL34x_REG_DATAX0);
	#endif
}
static int16_t get_y_axis(void)
{
	#if ADXL_I2C_Mode == 1
	return i2c_driver_read16(ADXL34x_REG_DATAY0);
	#endif
}
static int16_t get_z_axis(void)
{
	#if ADXL_I2C_Mode == 1
	return i2c_driver_read16(ADXL34x_REG_DATAZ0);
	#endif
}
uint8_t adxl34x_init(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	uint8_t getID= adxl34x_get_DeviceID(acc);
	if(getID != 0xE5)
	{
	return 255	;
	}
	  i2c_driver_write(ADXL34x_REG_INT_ENABLE, 0);  // Disable interrupts to start
	  /*ADXL34x_REG_THRESH_TAP The scale factor is 62.5 mg/LSB (that is, 0xFF = +16 g).
	  A value of 0 may result in undesirable behavior if single-tap/
	  double-tap interrupts are enabled.*/
	  i2c_driver_write(ADXL34x_REG_THRESH_TAP, 0x16);
	  i2c_driver_write(ADXL34x_REG_DUR, 50);        // Max tap duration, 625 µs/LSB
	  /*ADXL34x_REG_LATENT: The scale factor is 1.25 ms/LSB. 
	  A value of 0 disables the double-tap function*/
	  i2c_driver_write(ADXL34x_REG_LATENT,0);
	  i2c_driver_write(ADXL34x_REG_WINDOW,0); // Waiting period,  1.25 ms/LSB, 0=no double tap
	  /*you can also enable sign XYZ bits*/
	  i2c_driver_write(ADXL34x_REG_TAP_AXES, 0x7); // Enable the XYZ axis for tap

	  // Enable measurements
	  /*
								 ADXL34x_REG_POWER_CTL
		D7		D6		D5		D4				  D3			D2			D1	D0
		0		0		Link	AUTO_SLEEP		Measure		   Sleep		Wakeup
	  */
	  i2c_driver_write(ADXL34x_REG_POWER_CTL, 0x08);
	#endif
	return adxl_error_non;
}
uint8_t adxl34x_get_DeviceID(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	return i2c_driver_read(ADXL34x_REG_DEVID);
	#endif
}

uint8_t adxl34x_set_Range(struct Acc_adxl34x_t *acc,uint8_t range)
{
	switch (range)
	{
		case ADXL343_RANGE_2_G :
		acc->g_factor= 2;
		break;
		case ADXL343_RANGE_4_G :
		acc->g_factor= 4;
		break;
		case ADXL343_RANGE_8_G :
		acc->g_factor= 8;
		break;
		case ADXL343_RANGE_16_G :
		acc->g_factor= 16;
		break;
	}
	#if ADXL_I2C_Mode == 1
	  uint8_t format = i2c_driver_read(ADXL34x_REG_DATA_FORMAT);

	  /* Update the data rate */
	  format &= ~0x0F;
	  format |= range;

	  /* Make sure that the FULL-RES bit is enabled for range scaling */
	  format |= 0x08;

	  /* Write the register back to the IC */
	  i2c_driver_write(ADXL34x_REG_DATA_FORMAT, format);

	  /* Keep track of the current range (to avoid read back) */
	  acc->range = range;
	return adxl_error_non;
	#endif
}

uint8_t adxl34x_get_Range(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	return i2c_driver_read(ADXL34x_REG_DATA_FORMAT) & 0x03;
	#endif
}

uint8_t adxl34x_set_DataRate(struct Acc_adxl34x_t *acc,uint8_t dataRate){
  /* Note: The LOW_POWER bits are currently ignored and we always keep
     the device in 'normal' mode */
  acc->rate=dataRate;
  #if ADXL_I2C_Mode == 1
  i2c_driver_write(ADXL34x_REG_BW_RATE, dataRate);
  return adxl_error_non;
  #endif
}

uint8_t adxl34x_get_DataRate(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	 return i2c_driver_read(ADXL34x_REG_BW_RATE) & 0x0F;
    #endif
}

void adxl34x_refresh_xyz(struct Acc_adxl34x_t *acc)
{
		acc->raw_x=get_x_axis();
		acc->raw_y=get_y_axis();
		acc->raw_z=get_z_axis();
		
		acc->x_axis= acc->raw_x * ADXL34x_MG2G_MULTIPLIER * acc->g_factor;
		acc->y_axis= acc->raw_y * ADXL34x_MG2G_MULTIPLIER * acc->g_factor;
		acc->z_axis= acc->raw_z * ADXL34x_MG2G_MULTIPLIER * acc->g_factor;
		//return i2c_driver_read(ADXL34x_REG_BW_RATE) & 0x0F;
}

void adxl34x_get_axisOffset(struct Acc_adxl34x_t *acc)
{
	 #if ADXL_I2C_Mode == 1
	acc->offset_x_axis = i2c_driver_read(ADXL34x_REG_OFSX);
	acc->offset_y_axis = i2c_driver_read(ADXL34x_REG_OFSY);
	acc->offset_z_axis = i2c_driver_read(ADXL34x_REG_OFSZ);
	 #endif
}
void adxl34x_set_axisOffset(struct Acc_adxl34x_t *acc,int8_t x_offset,int8_t y_offset,int8_t z_offset)
{
	 #if ADXL_I2C_Mode == 1
	 i2c_driver_write(ADXL34x_REG_OFSX, x_offset);
	 i2c_driver_write(ADXL34x_REG_OFSY, y_offset);
	 i2c_driver_write(ADXL34x_REG_OFSZ, z_offset);
	// return adxl_error_non;
	 #endif
}

void adxl34x_set_zeroOffset(struct Acc_adxl34x_t *acc)
{
	/*to start this test , we have to get 10 samples in average first*/
	int32_t X0gt=0;
	int32_t Y0gt=0;
	int32_t Z0gt=0;
	int16_t X0g=0;
	int16_t Y0g=0;
	int16_t Z0g=0;
	uint16_t time_delay=0;
	uint8_t  num_of_sample=10;/*default value*/
	acc->offset_x_axis=0;
	acc->offset_y_axis=0;
	acc->offset_z_axis=0;
	switch (acc->rate)
	{
	 case ADXL34x_DATARATE_0_10_HZ :
	 time_delay=10000; /*in millisecond*/	 
	 break;	
	 case ADXL34x_DATARATE_0_20_HZ :
	 time_delay=5000; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_0_39_HZ :
	 time_delay=2560; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_0_78_HZ :
	 time_delay=1285; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_1_56_HZ :
	 time_delay=650; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_3_13_HZ :
	 time_delay=320; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_6_25HZ :
	 time_delay=160; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_12_5_HZ :
	 time_delay=80; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_25_HZ :
	 time_delay=40; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_50_HZ :
	 time_delay=20; /*in millisecond*/
	 break;
	 case ADXL34x_DATARATE_100_HZ :
	 time_delay=10; /*in millisecond*/
	 break;
	 default:
	 /*for any data rate above 100Hz , but need 0.1 sec worth of samples */
	 time_delay=5; /*in millisecond*/
	 num_of_sample=40; /*40 samples in total */
	 break;
	}
	 #if ADXL_I2C_Mode == 1
	 /*first you should delete any previous offset data*/
	 adxl34x_set_axisOffset(acc,acc->offset_x_axis,acc->offset_y_axis,acc->offset_z_axis);
	 i2c_delay_ms(40);
	 get_x_axis();
	 get_y_axis();
	 get_z_axis();
	 i2c_delay_ms(time_delay);
	 for (uint8_t i=0;i<num_of_sample;i++)
	 {
		 X0gt+=get_x_axis();
		 Y0gt+=get_y_axis();
		 Z0gt+=get_z_axis();
		 i2c_delay_ms(time_delay);
	 }
	 #endif
	 
	 /*we have to take the average of the readings*/
	 X0g=(int16_t)X0gt/num_of_sample;
	 Y0g=(int16_t)Y0gt/num_of_sample;
	 Z0g=(int16_t)(Z0gt/num_of_sample) - 256 ;
	 
	 acc->offset_x_axis = round(X0g/4) *-1;
	 acc->offset_y_axis = round(Y0g/4) *-1;
	 acc->offset_z_axis = round(Z0g/4) *-1;
	 adxl34x_set_axisOffset(acc,acc->offset_x_axis,acc->offset_y_axis,acc->offset_z_axis);
}

uint8_t adxl34x_enableInterrupt(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	i2c_driver_write(ADXL34x_REG_INT_ENABLE, acc->IRQ_source);
	#endif
	 return adxl_error_non;
}

uint8_t adxl34x_disableInterrupt(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	i2c_driver_write(ADXL34x_REG_INT_ENABLE, irq_src_disable);
	#endif
	return adxl_error_non;
}

uint8_t adxl34x_set_mapInterrupt(struct Acc_adxl34x_t *acc,uint8_t irq_pin,uint8_t src)
{
	#if ADXL_I2C_Mode == 1
	/*first read the existing value*/
	uint8_t mIrq=adxl34x_get_mapInterrupt(acc);
	printf("before mIrq=%02d\r\n",mIrq);
	mIrq |= (irq_pin << src);
	printf("after mIrq=%02d\r\n",mIrq);
	i2c_driver_write(ADXL34x_REG_INT_MAP, mIrq);
	#endif
	return adxl_error_non;
}

uint8_t adxl34x_get_mapInterrupt(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	/*first read the existing value*/
	return i2c_driver_read(ADXL34x_REG_INT_MAP);
	#endif
}
uint8_t adxl34x_get_Interrupt_Status(struct Acc_adxl34x_t *acc)
{
	#if ADXL_I2C_Mode == 1
	/*first read the existing value*/
	return i2c_driver_read(ADXL34x_REG_INT_SOURCE);
	#endif
}
/*
uint8_t adxl34x_get_Interrupt(struct Acc_adxl34x_t *acc)
{
	 uint8_t format = i2c_driver_read(ADXL34x_REG_INT_SOURCE);
	 return format;
}
*/