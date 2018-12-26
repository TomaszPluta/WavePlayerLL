/*
 * dac.c
 *
 *  Created on: 09.12.2018
 *      Author: tomek
 */

#include "dac.h"
#include  "stm32f3xx_ll_dac.h"
#include "stm32f3xx.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_gpio.h"

dac::dac(){


  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->AHBENR |= RCC_AHBENR_DMA2EN;
  RCC->APB1ENR |= RCC_APB1ENR_DAC1EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

  GPIOA->MODER |= GPIO_MODER_MODER4_1;
  GPIOA->AFR[0] |= (1<<16) | (1<<19);

}


dac::dac(uint8_t * waveSampleArray, uint32_t  waveSampleNb){



	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

	  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ALTERNATE);
	  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_4, LL_GPIO_AF_9);



	  //DAC->CR = DAC_CR_DMAEN1 | DAC_CR_TEN1 |  DAC_CR_EN1;

	  LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_1,LL_DAC_TRIG_EXT_TIM6_TRGO );
	  LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_1);
	  LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);
	  LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);


	  LL_TIM_SetAutoReload(TIM6, 30);
	  LL_TIM_SetPrescaler(TIM6, 300);
	  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
	  LL_TIM_EnableARRPreload(TIM6);
	  LL_TIM_EnableCounter(TIM6);



	  DMA2_Channel3->CNDTR = waveSampleNb; // number of data to transfer
	  DMA2_Channel3->CPAR = (uint32_t)&(DAC->DHR8R1);
	  DMA2_Channel3->CMAR = (uint32_t)waveSampleArray; //memory address register
	  DMA2_Channel3->CCR = DMA_CCR_MINC | DMA_CCR_CIRC  | DMA_CCR_DIR | DMA_CCR_EN; // enable circular, memory increment,  dir from memory to dac
}



void dac::dacLL(uint8_t * waveSampleArray, uint32_t  waveSampleNb){
	  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	  RCC->AHBENR |= RCC_AHBENR_DMA2EN;
	  RCC->APB1ENR |= RCC_APB1ENR_DAC1EN;
	  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	  GPIOA->MODER |= GPIO_MODER_MODER4_1;
	  GPIOA->AFR[0] |= (1<<16) | (1<<19);

	  DAC->CR = DAC_CR_DMAEN1 | DAC_CR_TEN1 |  DAC_CR_EN1;

//	  TIM6->ARR = 30;       // sampling freq (with prescaler)
//	  TIM6->PSC = 300;       //prescaler
//	  TIM6->CR2 |= TIM_CR2_MMS_1; // TRGO generated while timer overrun
//	  TIM6->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // TIM6 enable


	  LL_TIM_SetAutoReload(TIM6, 30);
	  LL_TIM_SetPrescaler(TIM6, 300);
	  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
	  LL_TIM_EnableARRPreload(TIM6);
	  LL_TIM_EnableCounter(TIM6);


	  DMA2_Channel3->CNDTR = waveSampleNb; // number of data to transfer
	  DMA2_Channel3->CPAR = (uint32_t)&(DAC->DHR8R1);
	  DMA2_Channel3->CMAR = (uint32_t)waveSampleArray; //memory address register
	  DMA2_Channel3->CCR = DMA_CCR_MINC | DMA_CCR_CIRC  | DMA_CCR_DIR | DMA_CCR_EN; // enable circular, memory increment,  dir from memory to dac
}



