/*
 * dac.h
 *
 *  Created on: 09.12.2018
 *      Author: tomek
 */

#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"

class dac{

public:
	dac();
	dac(uint8_t * waveSampleArray, uint32_t  waveSampleNb);
	void dacLL(uint8_t * waveSampleArray, uint32_t  waveSampleNb);

};



#endif /* DAC_H_ */
