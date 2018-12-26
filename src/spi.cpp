/*
 * spi2.cpp
 *
 *  Created on: 10.12.2018
 *      Author: tomek
 */


#include "spi.h"
#include "stm32f3xx.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_spi.h"

SpiDriver::SpiDriver(void){


	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);


	/*CS Pin*/
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_12, LL_GPIO_PULL_UP);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_HIGH);

	/*SPI Hardware controlled Pin*/
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_13, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_14, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_15, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);


	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_13, LL_GPIO_AF_5);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_14, LL_GPIO_AF_5);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_15, LL_GPIO_AF_5);


	LL_SPI_SetRxFIFOThreshold(SPI2, LL_SPI_RX_FIFO_TH_QUARTER);
	LL_SPI_InitTypeDef SPI_InitStruct;
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPoly = 0;
	SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	LL_SPI_Init(SPI2, &SPI_InitStruct);
	LL_SPI_Enable(SPI2);

}



void SpiDriver::SpiCsLow (void){
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
}
void SpiDriver::SpiCsHigh (void){
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
}




uint8_t SpiDriver::Transmit(uint8_t byte){
	while (!(LL_SPI_IsActiveFlag_TXE(SPI2)));
	LL_SPI_TransmitData8(SPI2,byte);
	while (!(LL_SPI_IsActiveFlag_RXNE(SPI2)));
	return LL_SPI_ReceiveData8(SPI2);
}







