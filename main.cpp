#include "defines.hpp"
#include "MPU9250.hpp"
#include "usart_xmega.hpp"

int main(){
    MPU9250::_START_RT_Gyro();
    while (1){
        usart_string(inoch(MPU9250::_RT_Gyro_Deg[0]));
        usart_string("   ");
        usart_string(inoch(MPU9250::_RT_Gyro_Deg[1]));
        usart_string("   ");
        usart_string(inoch(MPU9250::_RT_Gyro_Deg[2]));
        usart_send('\n');
    }
    return 0;
}