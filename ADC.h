/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Ahmed khaled
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_


#include"std_types.h"
#include"common_macros.h"
#include"micro_config.h"



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);


/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readchannel(uint8 channel_num);



#endif /* ADC_H_ */
