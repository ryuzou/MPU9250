//
// Created by root on 17/11/25.
//
#include "defines.hpp"
#include "MPU9250.hpp"


ISR(TCC0_OVF_vect){
    MPU9250::Get_RAW_Dat();
    if (!MPU9250::SPI_check()){
        return;
    }
    MPU9250::FLAG_GRAVITY_Update_timing++;
    if (MPU9250::FLAG_GRAVITY_Update_timing >= MPU9250::VGRAVITY_Update_timing) MPU9250::DesiseToAndUpdateGRAVITY();
    MPU9250::_RT_Gyro();

    return;
}

