//
// Created by root on 17/07/08.
//

#include "defines.hpp"
#include "SPI.hpp"

int SPI::SPI_READ(int addre) {
    SPI_SPI_NAME->CTRL = CONF;
	SPI_PORT_PORT->OUTCLR = SPI_PORT_PIN;
	SPI_SPI_NAME->DATA = addre;
	while (!(SPI_SPI_NAME->STATUS & 0x80));
	SPI_SPI_NAME->DATA = 0x00;
	while (!(SPI_SPI_NAME->STATUS & 0x80));
	int ret = SPI_SPI_NAME->DATA;
	SPI_PORT_PORT->OUTSET = SPI_PORT_PIN;
	delay_ms(1);
	return ret;
}

int SPI::SPI_WRITE(int addre, int val) {
    SPI_SPI_NAME->CTRL = CONF;
	SPI_PORT_PORT->OUTCLR = SPI_PORT_PIN;
	SPI_SPI_NAME->DATA = addre;
	while (!(SPI_SPI_NAME->STATUS & 0x80));
	SPI_SPI_NAME->DATA = val;
	while (!(SPI_SPI_NAME->STATUS & 0x80));
	SPI_PORT_PORT->OUTSET = SPI_PORT_PIN;
	delay_ms(1);
	return 0;
}

int SPI::SPI_TIMEOUT_CHECK(void) {
	while (!(SPI_SPI_NAME->STATUS & 0x80));
	return 0;
}

void SPI::SPI_CS_HIGH() {
	SPI_PORT_PORT->OUT = SPI_PORT_PIN;
}

void SPI::SPI_CS_LOW() {
	SPI_PORT_PORT->OUTCLR = SPI_PORT_PIN;
}


bool SPI::SPI_CONFIG(SPI_t *SPI_SPI_N, PORT_t *SPI_SPI_P, PORT_t *SPI_PORT_P, int SPI_PORT_PI, register8_t CONFIG) {
	SPI_SPI_NAME = SPI_SPI_N;
	SPI_SPI_PORT = SPI_SPI_P;
	SPI_PORT_PORT = SPI_PORT_P;
	SPI_PORT_PIN = SPI_PORT_PI;
	SPI_SPI_PORT->DIRCLR = 0x00;
	SPI_SPI_PORT->DIRCLR = PIN6_bm;
	SPI_SPI_PORT->DIRSET = PIN4_bm | PIN5_bm | PIN7_bm;
	SPI_PORT_PORT->OUTSET = SPI_PORT_PIN;
    CONF = CONFIG;
	SPI_SPI_N->CTRL = CONF;
	return 0;
}

void SPI::SPI_ALL_CLEAR() {
	SPI_SPI_NAME->CTRL = 0x00;
	SPI_SPI_PORT->DIR = 0x00;
}