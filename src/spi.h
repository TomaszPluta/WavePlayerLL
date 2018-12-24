/*
 * spi.h
 *
 *  Created on: 10.12.2018
 *      Author: tomek
 */

#ifndef SPI_H_
#define SPI_H_

#include "stdint.h"





class SpiDriver{

public:
	SpiDriver();
	static  uint8_t Transmit (uint8_t data);
	static void SpiCsLow (void);
	static void SpiCsHigh (void);
};



#endif /* SPI_H_ */
