/*
 * spi2.cpp
 *
 *  Created on: 10.12.2018
 *      Author: tomek
 */


#include "spi.h"
#include "stm32f3xx.h"


SpiDriver::SpiDriver(void){
//	RCC->APB1RSTR |=  RCC_APB1RSTR_SPI2RST;
//	RCC->APB1RSTR &=  ~RCC_APB1RSTR_SPI2RST;
//
//	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
//
//
//	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
//
//	GPIOB->MODER |= GPIO_MODER_MODER12_0;
//	GPIOB->MODER |= GPIO_MODER_MODER13_1;
//	GPIOB->MODER |= GPIO_MODER_MODER14_1;
//	GPIOB->MODER |= GPIO_MODER_MODER15_1;
//
//
//	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
//	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
//	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;
//	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
//
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







