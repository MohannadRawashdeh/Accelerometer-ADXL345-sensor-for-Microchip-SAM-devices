/*
 * ADXL34x_I2C.c
 *
 * Created: 4/2/2020 1:28:45 AM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "ADXL345/ADXL34x.h"
struct _i2c_m_msg i2c_msg;
#define wr_buf_size  2
static uint8_t write_buf[wr_buf_size];
static uint8_t read_buf [wr_buf_size];
void i2c_driver_write(uint8_t reg,uint8_t data)
{
	/*write one byte to the sensor*/
	write_buf[0]=reg;
	write_buf[1]=data;

	i2c_msg.addr   = ADXL34x_ADDRESS;
	i2c_msg.flags  = I2C_M_STOP;
	i2c_msg.buffer = write_buf;
	i2c_msg.len    = wr_buf_size;

	i2c_m_sync_transfer(&I2C_ADXL345, &i2c_msg);
}
uint8_t i2c_driver_read(uint8_t reg)/**/
{
	i2c_m_sync_cmd_read(&I2C_ADXL345,reg,read_buf,1);
	return read_buf[0];
}

int16_t i2c_driver_read16(uint8_t reg)/*only to read the accel. data*/
{
	i2c_m_sync_cmd_read(&I2C_ADXL345,reg,read_buf,2);
	return (uint16_t)(read_buf[0] | read_buf[1] << 8);
}

uint16_t i2c_delay_us(uint16_t tdelay)
{
	 delay_us(tdelay);
	 return 0;
}

uint16_t i2c_delay_ms(uint16_t tdelay)
{
	delay_ms(tdelay);
	return 0;
}