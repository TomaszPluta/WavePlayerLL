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

SpiDriver::SpiDriver(void){

	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);


	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_12, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_13, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_14, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_15, LL_GPIO_MODE_ALTERNATE);


	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);

//	GPIOB->PUPDR|= GPIO_PUPDR_PUPDR12_0;
//
//
//
//	GPIOB->AFR[1] |= (1<<20) | (1<<22);
//	GPIOB->AFR[1] |= (1<<24) | (1<<26);
//	GPIOB->AFR[1] |= (1<<28) | (1<<30);
//
//
//	SPI2->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_2 ;
//	SPI2->CR1 |= SPI_CR1_MSTR;
//	SPI2->CR1 |=  SPI_CR1_SSM;
//	SPI2->CR1 |=  SPI_CR1_SSI;
//
//	SPI2->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2;
//	SPI2->CR2 |= SPI_CR2_FRXTH;
//	SPI2->CR2 |= SPI_CR2_SSOE;
//
//	SPI2->CR1 |= SPI_CR1_SPE;

}



void SpiDriver::SpiCsLow (void){
	GPIOB->ODR &= ~GPIO_ODR_12;
}
void SpiDriver::SpiCsHigh (void){
	GPIOB->ODR |= GPIO_ODR_12;
}




uint8_t SpiDriver::Transmit(uint8_t byte){
	while (!(SPI2->SR & SPI_SR_TXE));
	*(__IO uint8_t *) &(SPI2->DR) = byte;
	while (!(SPI2->SR & SPI_SR_RXNE));
	return *(uint8_t *)&(SPI2->DR);
}







