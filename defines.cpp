//
// Created by root on 17/12/16.
//
#include "defines.hpp"

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
