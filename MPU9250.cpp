//
// Created by root on 17/11/23.
//

#include "defines.hpp"
#include "MPU9250.hpp"
#include "SPI.hpp"

namespace MPU9250{

    SPI MPU_9250;

    bool Config(){
        SPI_Config();
        ResetValue();
    }

    void ResetValue(){
        FLAG_if_SPI_ConfigHasDone = 0;
        FLAG_if_using_RTAccel = 0;
        FLAG_if_using_RTGyro = 0;
        FLAG_if_using_RTMagnDeg = 0;
        GetGRAVITYvalue(9.8);
        MDatUpdateSEC = DEFMDatUpdateSEC;
        VGRAVITY_Update_timing = 0;
        for (int i = 0; i < 3; ++i) {
            ARAW_Accel_dat[i] = 0;
            GRAW_Accel_dat[i] = 0;
            RAW_Gyro_dat[i] = 0;
            _RT_Gyro_DPS[i] = 0;
            _RT_Gyro_Deg[i] = 0;
            _RT_Gyro_Rad[i] = 0;
            for (int j = 0; j < 20; ++j) {
                RAW_Past_Gyro_dat[j][i] = 0;
                RAW_Past_Accel_dat[j][i] = 0;
            }
        }
    }
    
    bool SPI_Config(){
        MPU_9250.SPI_CONFIG(&MPU9250_SPISPI, &MPU9250_SPIPORT, &MPU9250_SPI_CSPORT, MPU9250_SPI_CSPIN,
                           SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV64_gc);
        FLAG_if_SPI_ConfigHasDone = 1;
        return 0;
    }

    int READ(int addre){
        if (SPI_check()) return NULL;
        return MPU_9250.SPI_READ(addre | 0x80);
    }

    int WRITE(int addre, int val){
        if (SPI_check()) return -1;
        MPU_9250.SPI_WRITE(addre, val);
        return 0;
    }

    int SPI_check() {
        if (!FLAG_if_SPI_ConfigHasDone) return -1;
        if (READ(0x75) == 0x71) return 1;
        return 0;
    }
    
    bool GetGRAVITYvalue(double PreGra){
        if (!PreGra){
            GRAVITY = PreGra;
            return 1;
        }
        GRAVITY = sqrt(pow((double)ARAW_Accel_dat[0], 2.0) + pow((double)ARAW_Accel_dat[1], 2.0) + pow((double)ARAW_Accel_dat[2], 2.0));
    }

    void DesiseToAndUpdateGRAVITY() {
        double PreGrav = sqrt(pow((double)ARAW_Accel_dat[0], 2.0) + pow((double)ARAW_Accel_dat[1], 2.0) + pow((double)ARAW_Accel_dat[2], 2.0));
        if (PreGrav < 10 && PreGrav > 9.7)
            GetGRAVITYvalue(PreGrav);
    }
    
    int Get_RAW_Dat() {
        double accel[3] = {0};
        double gyro[3] = {0};
        int16_t dat[3] = {0};
        unsigned int dat2[3] = {0};
        dat[0]  = MPU_9250.SPI_READ(0x3B | 0x80) << 8;
        dat[0] |= MPU_9250.SPI_READ(0x3C | 0x80) & 0x00ff;
        accel[0] = ((2.0 / (float) 0x8000) * dat[0]);
        dat[1] = MPU_9250.SPI_READ(0x3D | 0x80) << 8;
        dat[1] = MPU_9250.SPI_READ(0x3E | 0x80) & 0x00ff;
        accel[1] = ((2.0 / (float) 0x8000) * dat[1]);
        dat[2] = MPU_9250.SPI_READ(0x3F | 0x80) << 8;
        dat[2] = MPU_9250.SPI_READ(0x3F + 1 | 0x80) & 0x00ff;
        accel[2] = ((2.0 / (float) 0x8000) * dat[2]);
        dat2[0] = MPU_9250.SPI_READ(0x43 | 0x80) << 8;
        dat2[0] = MPU_9250.SPI_READ(0x44 | 0x80) & 0x00ff;
        gyro[0] = ((1000 / (float) 0x8000) * dat2[0]);
        dat2[1] = MPU_9250.SPI_READ(0x45 | 0x80) << 8;
        dat2[1] = MPU_9250.SPI_READ(0x46 | 0x80) & 0x00ff;
        gyro[1] = ((1000 / (float) 0x8000) * dat2[1]);
        dat2[2] = MPU_9250.SPI_READ(0x47 | 0x80) << 8;
        dat2[2] = MPU_9250.SPI_READ(0x48 | 0x80) & 0x00ff;
        gyro[2] = ((1000 / (float) 0x8000) * dat2[2]);
        for (int i = 0; i < 3; ++i) {
            ARAW_Accel_dat[i] = accel[i] * GRAVITY;
            GRAW_Accel_dat[i] = accel[i];
            RAW_Gyro_dat[i] = gyro[i];
        }
        return 0;
    }

    bool _START_RT_Gyro(){
        if (!FLAG_if_SPI_ConfigHasDone)
            Config();
        PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
        TCC0.CTRLA = TC_CLKSEL_DIV4_gc;
        TCC0.CTRLB = TC_WGMODE_NORMAL_gc;
        TCC0.PER = 4 * MDatUpdateSEC;
        FLAG_if_using_RTGyro = 1;
        for (int i = 0; i < 3; ++i) {
            _RT_Gyro_DPS[i] = 0;
            _RT_Gyro_Deg[i] = 0;
            _RT_Gyro_Rad[i] = 0;
        }
    }

    void _RESET_RT_Gyro(){
        _START_RT_Gyro();
    }

    void _RT_Gyro(){ //TODO
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 3; ++j) {
                RAW_Past_Gyro_dat[i][j] = RAW_Past_Gyro_dat[i + 1][j];
            }
        }
        Get_RAW_Dat();
        for (int k = 0; k < 3; ++k) {
            RAW_Past_Gyro_dat[0][k] = RAW_Gyro_dat[k];

        }
        for (int l = 0; l < 3; ++l) {
            _RT_Gyro_DPS[l] = RAW_Gyro_dat[l];
            _RT_Gyro_Deg[l] += (_RT_Gyro_DPS[l] * (double) MDatUpdateSEC) / (double) 10000;
        }
    }
}