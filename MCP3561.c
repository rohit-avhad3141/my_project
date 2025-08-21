/*
 * MCP3561.c
 *
 *  Created on: 22-Jun-2024
 *      Author: RnD
 */
#include "main.h"

#define ADC_CS_GPIO_Port GPIOA

#define ADC_IRQ_PORT GPIOC

/*adc define pins*/
#define CS       GPIO_PIN_4
#define SCK      GPIO_PIN_5
#define MOSI     GPIO_PIN_7
#define MISO     GPIO_PIN_6
#define IRQ_MDAT GPIO_PIN_4
#define MCLK     GPIO_PIN_3


#define MEAS_ARRAY_SIZE 10
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
// SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim5;

/* USER CODE BEGIN PV */
 uint8_t pTxData = 0b01000101, pRxData, spiTxBuff[4], spiRxBuff[4];
 uint32_t adc_data_samples[200], sample_no;
 uint8_t ary_ptr=0;
 unsigned char adc_samp[MEAS_ARRAY_SIZE][4];
 uint32_t samples_counter=0;
 float fAvgValue, Actual_mV, MCP3561_mV;
 uint32_t calc_ptr=0;
 uint32_t adc_count;

 float calc_adc_mv(uint8_t samp_indx)
 {
 /*	adc_stat = (adc_samp[samp_indx][0] & 0xC0) >> 6;
 	switch(adc_stat)
 	{
 		case 0x03:
 			adc_count = 0;
 			break;
 		case 0x01:
 			adc_count = ((adc_samp[samp_indx][0] & 0x3F)<<16)|(adc_samp[samp_indx][1]<<8)|adc_samp[samp_indx][2];
 			break;
 		case 0x00:
 			if(adc_samp[samp_indx][0] & 0x20) {													// Detect negative voltage
 				adc_count = 0x0;
 			} else {
 				adc_count = (adc_samp[samp_indx][0]<<16)|(adc_samp[samp_indx][1]<<8)|adc_samp[samp_indx][2];
 			}
 			break;
 		default:
 			adc_count = 0;
 			break;
 	}*/
 	if((adc_samp[samp_indx][0] & 0x01) == 0x01) {												// Negative input
 		adc_count = (adc_samp[samp_indx][1]<<16)|(adc_samp[samp_indx][2]<<8)|adc_samp[samp_indx][3];
 		adc_count = ((~adc_count) & 0x00FFFFFF) +1;
 		MCP3561_mV = (-1) * ((float)adc_count/(float)ADC_FULL_SCALE) * 750;//rangeFullVal[meas_range -1];
 	} else {
 		adc_count = (adc_samp[samp_indx][1]<<16)|(adc_samp[samp_indx][2]<<8)|adc_samp[samp_indx][3];
 		MCP3561_mV = ((float)adc_count/(float)ADC_FULL_SCALE) * 750;//rangeFullVal[meas_range -1];
 	}

 //	MCP3551_mV = (((float)adc_count/(float)ADC_FULL_SCALE) * (curr_gain * (float)curr_fix_gain * rShunt) / (volt_gain * (float)volt_fix_divider));

 	return MCP3561_mV;
 }
uint8_t MCP3561_register_get_length(uint8_t register_address)
{
  switch(register_address)
  {
    case 0x00:
    case 0x07:
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:
      return 3;
      break;
    case 0x0F:
    case 0x0E:
      return 2;
      break;
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x0C:
    case 0x0D:
      return 1;
      break;

    default:
      assert(0);
      break;
  }
  return 0;
}

void MCP3561_write_data(uint8_t register_address, uint8_t *data) {
	uint8_t spi_write[4], register_length, command_byte, i;
	mcp3561_spi_enable();																			// Enable ADC SPI

	register_length = MCP3561_register_get_length(register_address);

	command_byte = (MCP3561_SLAVE_ADDRESS << 6) | ((register_address & 0x0F) << 2) | (MCP3561_COMMAND_WRITE & 0x03);

	//command_byte=0b01001010;

	HAL_SPI_TransmitReceive(&hspi4, &command_byte, &pRxData, 1, 100);								// ADC CMD and get STATUS
	//HAL_SPI_Transmit(&hspi1, &command_byte, 1, 100);

	for(i = 0; i < register_length; i++)
        {
		spi_write[i] = data[register_length -1];
	    }

	HAL_SPI_Transmit(&hspi4, spi_write, register_length, 100);

	mcp3561_spi_disable();																			// Disable ADC SPI
}

void mcp3561_read_data(uint8_t register_address, uint8_t data_length,uint8_t *data)
{
	uint8_t command_byte;
	mcp3561_spi_enable();																			// Enable ADC SPI
   	//uint8_t spi_read_buffer = (uint8_t*)data;
	//uint8_t spi_read_buffer_end = data + data_length;
	data_length = MCP3561_register_get_length(register_address);

	command_byte = (MCP3561_SLAVE_ADDRESS << 6) | ((register_address & 0x0F) << 2) | (MCP3561_COMMAND_READ & 0x03);

	//command_byte=0b01001001;

	HAL_SPI_TransmitReceive(&hspi4, &command_byte, &pRxData, 1, 100);

	HAL_SPI_Receive(&hspi4, (uint8_t*)data, data_length, 100);

	mcp3561_spi_disable();	  // Disable ADC SPI
}

void mcp3561_read_adcData(void)
{
	uint8_t data[4];
	uint8_t volt1[4],volt2[4];

//	mcp3561_spi_enable();																			// Enable ADC SPI
//	HAL_SPI_TransmitReceive(&hspi1, spiTxBuff, &pRxData, 1, 100);

	HAL_SPI_Receive(&hspi4, (adc_samp + ary_ptr), 4, 100);
	ary_ptr++;
	if(ary_ptr >= MEAS_ARRAY_SIZE)
	{
		mcp3561_sampling_stop();
	}

//	   HAL_SPI_Receive(&hspi4, volt2/*(adc_samp + ary_ptr)*/, 4, 100);
//	   adc_count=(volt2[1]<<16|volt2[2]<<8|volt2[3]);
//	   float v2=((float)adc_count/(float)ADC_FULL_SCALE) * 1000;


//			HAL_SPI_Receive(&hspi1, *(adc_samp + ary_ptr), 3, 1);
//			ary_ptr++;
//			if(ary_ptr >= MEAS_ARRAY_SIZE) {
//				mcp3561_sampling_stop();
//			}

	//HAL_SPI_Receive(&hspi1, /*(adc_samp + ary_ptr)*/data, 4, 100);
	//HAL_Delay(100);

//	mcp3561_sampling_stop();
//
//
//	mcp3561_spi_disable();																							// Disable ADC SPI

//	adc_data_samples[sample_no++] = (spiRxBuff[0]<<16) | (spiRxBuff[1]<<8) | spiRxBuff[2];
}

void mcp3561_sampling_start(uint8_t ch)
{
    ary_ptr = 0;

	spiTxBuff[0] = MCP3561_CONFIG1_OSR_98304;																		//Set OSR
	MCP3561_write_data(MCP3561_CONFIG1, spiTxBuff);
//	mcp3561_read_data(MCP3561_CONFIG1, 1, spiRxBuff);

 	spiTxBuff[0] = (MCP3561_CONFIG3_CONV_MODE_CONT | MCP3561_CONFIG3_DATA_FORMAT_8SEXTENSION);																	//Conversion mode Continuous
	MCP3561_write_data(MCP3561_CONFIG3, spiTxBuff);
//	mcp3561_read_data(MCP3561_CONFIG3, 1, spiRxBuff);

 	spiTxBuff[0] = MCP3561_IRQ_MODE_IRQ | MCP3561_IRQ_MODE_HIGHZ | MCP3561_IRQ_FASTCMD_DIS | MCP3561_IRQ_STP_DIS;	//Configure IRQ
	MCP3561_write_data(MCP3561_IRQ, spiTxBuff);
//	mcp3561_read_data(MCP3561_IRQ, 1, spiRxBuff);

//	spiTxBuff[0] = MCP3561_MUX_VIN_PLUS_CH0 | MCP3561_MUX_VIN_MINUS_CH1;											//Select Channel
//	MCP3561_write_data(MCP3561_MUX, spiTxBuff);
//	mcp3561_read_data(MCP3561_MUX, 1, spiRxBuff);


	if(ch == 0)
	{
		spiTxBuff[0] = 0x08; //MCP3561_MUX_VIN_PLUS_CH0;// | MCP3561_MUX_VIN_MINUS_CH1;											//Select Channel
		MCP3561_write_data(MCP3561_MUX, spiTxBuff);
//		mcp3561_read_data(MCP3561_MUX, 1, spiRxBuff);
	}
	else if(ch == 1)
	{
		spiTxBuff[0] = 0x18; ///*MCP3561_MUX_VIN_PLUS_CH0; |*/  MCP3561_MUX_VIN_MINUS_CH1;											//Select Channel
		MCP3561_write_data(MCP3561_MUX, spiTxBuff);
//		mcp3561_read_data(MCP3561_MUX, 1, spiRxBuff);
	}


	spiTxBuff[0] = MCP3561_CONFIG0_CS_SEL_0 | MCP3561_CONFIG0_CLK_SEL_0 | MCP3561_CONFIG0_MODE_CONVERSION;			//Start conversion
	MCP3561_write_data(MCP3561_CONFIG0, spiTxBuff);
//	mcp3561_read_data(MCP3561_CONFIG0, 1, spiRxBuff);

	spiTxBuff[0] = (MCP3561_SLAVE_ADDRESS << 6) | ((MCP3561_ADCDATA & 0x0F) << 2) | (MCP3561_COMMAND_STATIC_READ & 0x03);

	mcp3561_spi_enable();																							// Enable ADC SPI
	HAL_SPI_TransmitReceive(&hspi4, spiTxBuff, &pRxData, 1, 100);

	//HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

void mcp3561_sampling_stop(void)
{
//	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);


	mcp3561_spi_disable();																							// Disable ADC SPI

//	spiTxBuff[0] = MCP3561_CONFIG0_CS_SEL_0 | MCP3561_CONFIG0_CLK_SEL_0 | MCP3561_CONFIG0_MODE_STANDBY;				//Conversion mode Standby
//	MCP3561_write_data(MCP3561_CONFIG0, spiTxBuff);


//	mcp3561_read_data(MCP3561_CONFIG0, 1, spiRxBuff);
}

void mcp3561_spi_enable(void)
{


	        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);            //Disable ADC
		//HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4, GPIO_PIN_RESET);		  //Enable ADC
		//HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);



}

void mcp3561_spi_disable(void)
{
                HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4, GPIO_PIN_RESET);		//Enable ADC
		//HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);


	        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);            //Disable ADC
        	//HAL_Delay(100);

}
