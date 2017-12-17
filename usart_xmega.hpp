/*
 * usart_xmega.h
 *
 * Created: 2017/05/08 17:09:11
 *  Author: robot
 */ 


#ifndef USART_XMEGA_H_
#define USART_XMEGA_H_

void init_usart(int baudrate);
void usart_send(char c);
void usart_string(const char *text);
void usart_putdec(uint16_t data);
void usart_puthex(uint16_t data);
void usart_puthex2(uint32_t data);


#endif /* USART_XMEGA_H_ */