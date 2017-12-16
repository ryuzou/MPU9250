//
// Created by root on 17/11/23.
//

#ifndef MPU9250_DEFINES_HPP
#define MPU9250_DEFINES_HPP

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <util/twi.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <stdint-gcc.h>
#include <math.h>

#define NOP 0x00
#define SPI_RW_TIMEOUT 1000

#define PI 3.14159263358979

#define MPU9250_SPISPI SPIE
#define MPU9250_SPIPORT PORTE
#define MPU9250_SPI_CSPORT PORTJ
#define MPU9250_SPI_CSPIN PIN0_bm


void SOFT_RESET(){
    RST.CTRL = RST_SWRST_bm;
}

void delay_us(int us){
    while(us){
        _delay_us(1);
        us--;
    }
}

void delay_ms(int ms){
    while(ms){
        _delay_us(1);
        ms--;
    }
}

void FreqTo32(void){
    OSC.CTRL |= 0x02;
    while ((OSC.STATUS & 0x02) == 0);
    CPU_CCP = 0xD8;
    CLK.CTRL = 0x01;
    CLK.PSCTRL = CLK_PSADIV0_bm;
    OSC.CTRL &= 0xFE;
}

char *inoch(int val) {
    char s[128] = {0};
    sprintf(s, "%d", val);
    return s;
}

#endif //MPU9250_DEFINES_HPP
