
#ifndef ADXL34X_H_
#define ADXL34X_H_

#include "atmel_start.h"
/*
 * ADXL345.h
 *
 * Created: 4/2/2020 12:55:31 AM
 *  Author: Mohannad Rawasdheh
 library based on Adafruit ADXL343 Library ,which must work for ADXL343/344/345 Sensors
 */ 
/**************************************************************************/
/*
    @author   K. Townsend (Adafruit Industries)
    BSD license (see license.txt)
    This is a library for the Adafruit ADS1015 breakout board
    ----> https://www.adafruit.com/products/???
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
    v1.0  - First release
*/
/**************************************************************************/
#ifndef ADXL_I2C_Mode
#define ADXL_I2C_Mode     0x01
#endif

#ifndef ADXL_SPI_Mode
#define ADXL_SPI_Mode     0x0
#endif
/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define ADXL34x_ADDRESS (0x53) /**< Assumes ALT address pin low */
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
#define ADXL34x_REG_DEVID			 (0x00)        /**< Device ID */
#define ADXL34x_REG_THRESH_TAP		 (0x1D)   /**< Tap threshold */
#define ADXL34x_REG_OFSX			 (0x1E)         /**< X-axis offset */
#define ADXL34x_REG_OFSY			 (0x1F)         /**< Y-axis offset */
#define ADXL34x_REG_OFSZ			 (0x20)         /**< Z-axis offset */
#define ADXL34x_REG_DUR				 (0x21)          /**< Tap duration */
#define ADXL34x_REG_LATENT			 (0x22)       /**< Tap latency */
#define ADXL34x_REG_WINDOW			 (0x23)       /**< Tap window */
#define ADXL34x_REG_THRESH_ACT		 (0x24)   /**< Activity threshold */
#define ADXL34x_REG_THRESH_INACT	 (0x25) /**< Inactivity threshold */
#define ADXL34x_REG_TIME_INACT		 (0x26)   /**< Inactivity time */
#define ADXL34x_REG_ACT_INACT_CTL    (0x27) /**< Axis enable control for activity and inactivity detection */
#define ADXL34x_REG_THRESH_FF		 (0x28) /**< Free-fall threshold */
#define ADXL34x_REG_TIME_FF			 (0x29)   /**< Free-fall time */
#define ADXL34x_REG_TAP_AXES		 (0x2A)  /**< Axis control for single/double tap */
#define ADXL34x_REG_ACT_TAP_STATUS	 (0x2B) /**< Source for single/double tap */
#define ADXL34x_REG_BW_RATE			 (0x2C)     /**< Data rate and power mode control */
#define ADXL34x_REG_POWER_CTL		 (0x2D)   /**< Power-saving features control */
#define ADXL34x_REG_INT_ENABLE		 (0x2E)  /**< Interrupt enable control */
#define ADXL34x_REG_INT_MAP			 (0x2F)     /**< Interrupt mapping control */
#define ADXL34x_REG_INT_SOURCE		 (0x30)  /**< Source of interrupts */
#define ADXL34x_REG_DATA_FORMAT		 (0x31) /**< Data format control */
#define ADXL34x_REG_DATAX0			 (0x32)      /**< X-axis data 0 */
#define ADXL34x_REG_DATAX1			 (0x33)      /**< X-axis data 1 */
#define ADXL34x_REG_DATAY0			 (0x34)      /**< Y-axis data 0 */
#define ADXL34x_REG_DATAY1			 (0x35)      /**< Y-axis data 1 */
#define ADXL34x_REG_DATAZ0			 (0x36)      /**< Z-axis data 0 */
#define ADXL34x_REG_DATAZ1			 (0x37)      /**< Z-axis data 1 */
#define ADXL34x_REG_FIFO_CTL		 (0x38)    /**< FIFO control */
#define ADXL34x_REG_FIFO_STATUS		 (0x39) /**< FIFO status */
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
#define ADXL34x_MG2G_MULTIPLIER (0.004) /**< 4mg per lsb */
/*=========================================================================*/

/** Used with register 0x2C (ADXL34x_REG_BW_RATE) to set bandwidth */

#define   ADXL34x_DATARATE_3200_HZ	      0b1111 /**< 3200Hz Bandwidth */
#define  ADXL34x_DATARATE_1600_HZ		  0b1110 /**< 1600Hz Bandwidth */
#define  ADXL34x_DATARATE_800_HZ		  0b1101  /**<  800Hz Bandwidth */
#define  ADXL34x_DATARATE_400_HZ		  0b1100  /**<  400Hz Bandwidth */
#define  ADXL34x_DATARATE_200_HZ		  0b1011  /**<  200Hz Bandwidth */
#define  ADXL34x_DATARATE_100_HZ		  0b1010  /**<  100Hz Bandwidth */
#define  ADXL34x_DATARATE_50_HZ		      0b1001   /**<   50Hz Bandwidth */
#define  ADXL34x_DATARATE_25_HZ		      0b1000   /**<   25Hz Bandwidth */
#define  ADXL34x_DATARATE_12_5_HZ		  0b0111 /**< 12.5Hz Bandwidth */
#define  ADXL34x_DATARATE_6_25HZ		  0b0110  /**< 6.25Hz Bandwidth */
#define  ADXL34x_DATARATE_3_13_HZ		  0b0101 /**< 3.13Hz Bandwidth */
#define  ADXL34x_DATARATE_1_56_HZ		  0b0100 /**< 1.56Hz Bandwidth */
#define  ADXL34x_DATARATE_0_78_HZ		  0b0011 /**< 0.78Hz Bandwidth */
#define  ADXL34x_DATARATE_0_39_HZ		  0b0010 /**< 0.39Hz Bandwidth */
#define  ADXL34x_DATARATE_0_20_HZ		  0b0001 /**< 0.20Hz Bandwidth */
#define  ADXL34x_DATARATE_0_10_HZ		  0b0000  /**< 0.10Hz Bandwidth (default value) */


/** Used with register 0x31 (ADXL34x_REG_DATA_FORMAT) to set g range */
#define  ADXL343_RANGE_16_G  0x03 /**< +/- 16g */
#define  ADXL343_RANGE_8_G   0x02  /**< +/- 8g */
#define  ADXL343_RANGE_4_G   0x01  /**< +/- 4g */
#define  ADXL343_RANGE_2_G   0x00   /**< +/- 2g (default value) */

/** Possible interrupts sources on the ADXL34x. */
  #define   irq_src_disable        0
  #define   irq_src_overrun	       1/**< Bit 0 */
  #define   irq_src_watermark      2/**< Bit 1 */
  #define   irq_src_freefall       4/**< Bit 2 */
  #define   irq_src_inactivity     8/**< Bit 3 */
  #define   irq_src_activity	  16	/**< Bit 4 */
  #define   irq_src_double_tap    32 /**< Bit 5 */
  #define   irq_src_single_tap    64 /**< Bit 6 */
  #define   irq_src_data_ready   128 /**< Bit 7 */
               /**< Individual bits in the bitfield. */

  #define   irq_map_overrun		  0
  #define   irq_map_watermark     1/**< Bit 1 */
  #define   irq_map_freefall      2/**< Bit 2 */
  #define   irq_map_inactivity    3/**< Bit 3 */
  #define   irq_map_activity	  4	/**< Bit 4 */
  #define   irq_map_double_tap    5 /**< Bit 5 */
  #define   irq_map_single_tap    6 /**< Bit 6 */
  #define   irq_map_data_ready    7 /**< Bit 7 */
/** Possible interrupt pin outputs on the ADXL34x. */
#define ADXL34x_IRQ1  0
#define ADXL34x_IRQ2  1

#define adxl_error_non  0

struct Acc_adxl34x_t
{
	float x_axis;
	float y_axis;
	float z_axis;
	int16_t raw_x;
	int16_t raw_y;
	int16_t raw_z;
	int16_t range ;
	uint8_t IRQ_source;
	int8_t  resolution; /*10 bit or full range*/
	int8_t  rate ;
	int16_t offset_x_axis;
	int16_t offset_y_axis;
	int16_t offset_z_axis;
	int8_t  g_factor;
};

#if ADXL_I2C_Mode == 1
void	 i2c_driver_write(uint8_t reg,uint8_t data);
uint8_t  i2c_driver_read(uint8_t reg);/**/
int16_t  i2c_driver_read16(uint8_t reg);/*only to read the accel. data*/
uint16_t i2c_delay_us(uint16_t tdelay);
uint16_t i2c_delay_ms(uint16_t tdelay);
#endif

uint8_t adxl34x_init(struct Acc_adxl34x_t *acc);
uint8_t adxl34x_get_DeviceID(struct Acc_adxl34x_t *acc);

uint8_t adxl34x_set_Range(struct Acc_adxl34x_t *acc,uint8_t range);
uint8_t adxl34x_get_Range(struct Acc_adxl34x_t *acc);

uint8_t adxl34x_set_DataRate(struct Acc_adxl34x_t *acc,uint8_t dataRate);
uint8_t adxl34x_get_DataRate(struct Acc_adxl34x_t *acc);

void adxl34x_refresh_xyz(struct Acc_adxl34x_t *acc);


void adxl34x_get_axisOffset(struct Acc_adxl34x_t *acc);
void adxl34x_set_axisOffset(struct Acc_adxl34x_t *acc,int8_t x_offset,int8_t y_offset,int8_t z_offset);

void adxl34x_set_zeroOffset(struct Acc_adxl34x_t *acc);

uint8_t adxl34x_enableInterrupt(struct Acc_adxl34x_t *acc);
uint8_t adxl34x_disableInterrupt(struct Acc_adxl34x_t *acc);

uint8_t adxl34x_set_mapInterrupt(struct Acc_adxl34x_t *acc,uint8_t irq_pin,uint8_t src);
uint8_t adxl34x_get_mapInterrupt(struct Acc_adxl34x_t *acc);

uint8_t adxl34x_get_Interrupt_Status(struct Acc_adxl34x_t *acc);
/*
uint8_t adxl34x_get_Interrupt(struct Acc_adxl34x_t *acc);
*/
#endif /* ADXL34X_H_ */