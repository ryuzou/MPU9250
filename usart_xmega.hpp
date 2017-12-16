/*
 * usart_xmega.h
 *
 * Created: 2017/05/08 17:09:11
 *  Author: robot
 */ 


#ifndef USART_XMEGA_H_
#define USART_XMEGA_H_

//#define UARTBAUD ((uint16_t)(F_CPU/(16*baudrate)-1))
#define UARTBAUD(b) ((unsigned long)(F_CPU)/16/(unsigned long)b-1)


void init_usart(int baudrate);
void usart_send(char c);
void usart_string(const char *text);
void usart_putdec(uint16_t data);
void usart_puthex(uint16_t data);
void usart_puthex2(uint32_t data);


void init_usart(int baudrate){ //32MHzで38400ボーレート
	//uint16_t UARTBAUD = ((uint16_t)(F_CPU/(16*baudrate)-1));
	PORTC.DIRSET=PIN3_bm;
	PORTC.DIRCLR=PIN2_bm;
	//USARTC0.BAUDCTRLA = UARTBAUD;
	//USARTC0.BAUDCTRLB = (UARTBAUD)>>8 ;
	USARTC0.BAUDCTRLA=51;//UARTBAUD(baudrate)&0xff;
	USARTC0.BAUDCTRLB=0;//UARTBAUD(baudrate)>>8;
	USARTC0.CTRLC = USART_CHSIZE_8BIT_gc;
	USARTC0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	usart_puthex2(UARTBAUD(baudrate));
}
void usart_send(char c)
{

	while( !(USARTC0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty

	USARTC0_DATA = c;

}
void usart_string(const char *text)
{
	while(*text)
	{
		usart_send(*text++);
	}
}
void usart_putdec(uint16_t data){
	usart_send(data/1000 + '0');
	data %= 1000;
	usart_send(data/100 + '0');
	data %= 100;
	usart_send(data/10 + '0');
	data %= 10;
	usart_send(data + '0');
}
void usart_puthex(uint16_t data){
	//usart_send(data/1000000 + '0');
	//data %= 1000000;
	//usart_send(data/100000 + '0');
	//data %= 100000;
	usart_send(data/10000 + '0');
	data %= 10000;
	usart_send(data/1000 + '0');
	data %= 1000;
	usart_send(data/100 + '0');
	data %= 100;
	usart_send(data/10 + '0');
	data %= 10;
	usart_send(data + '0');
}
void usart_puthex2(uint32_t data){
	usart_send(data/100000000000 + '0');
	data %= 100000000000;
	usart_send(data/10000000000 + '0');
	data %= 10000000000;
	usart_send(data/1000000000 + '0');
	data %= 1000000000;
	usart_send(data/100000000 + '0');
	data %= 100000000;
	usart_send(data/10000000 + '0');
	data %= 10000000;
	usart_send(data/1000000 + '0');
	data %= 1000000;
	usart_send(data/100000 + '0');
	data %= 100000;
	usart_send(data/10000 + '0');
	data %= 10000;
	usart_send(data/1000 + '0');
	data %= 1000;
	usart_send(data/100 + '0');
	data %= 100;
	usart_send(data/10 + '0');
	data %= 10;
	usart_send(data + '0');
}





#endif /* USART_XMEGA_H_ */