#ifndef _AiP33A06_H
#define _AiP33A06_H
#include "AiP33A06.h"	
// #define SDA P35
// #define CLK P34
#define slave_addr 0x78//写数据时的从机地址//cs1=cs2=0
#define slave_addr1 0x79//读数据时的从机地址
void iic_stop(void);
void AiP33A06_writecmd(unsigned char dat);
void AiP33A06_ACK(void);
void AiP33A06_writebyte(unsigned char dat);
void write_data(unsigned char addr,unsigned char pwm);
void Ram_Clear(void);
void sysinit(void);
void display(void);
// void delay(void);
// void delay_ms(unsigned int k);
#endif
