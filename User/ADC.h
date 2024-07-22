#ifndef __ADC_H
#define __ADC_H
#include <stdint.h>

void adc_init(void);
void adc_channel_config(uint8_t channel);
void adc_channels_config(uint8_t *channel,uint8_t num);
void adc_enable(void);
void adc_disable(void);
void adc_start(void);
uint16_t adc_dr(void);
uint16_t adc_vcc(void);
uint16_t GetADCValue(uint32_t ADC_Channel);
uint16_t Adc_CalBatRef(void);
void delay_us(uint16_t us);

#endif

