//
// Created by root on 17/11/23.
//

#ifndef MPU9250_MPU9250_HPP
#define MPU9250_MPU9250_HPP

#define DEFMDatUpdateSEC 1

namespace MPU9250{

    //region Description
    extern double ARAW_Accel_dat[3];
    extern double GRAW_Accel_dat[3];
    extern double RAW_Gyro_dat[3];

    extern double RAW_Past_Accel_dat[20][3];   //little value is younger.
    extern double RAW_Past_Gyro_dat[20][3];   //little value is younger.

    extern double _RT_Gyro_DPS[3];
    extern long double _RT_Gyro_Deg[3];
    extern long double _RT_Gyro_Rad[3];

    extern bool FLAG_if_using_RTGyro;
    extern bool FLAG_if_using_RTAccel;
    extern bool FLAG_if_using_RTMagnDeg;

    extern double GRAVITY;     //In M/Sec^2

    extern int FLAG_GRAVITY_Update_timing;
    extern int VGRAVITY_Update_timing;
    extern int MDatUpdateSEC;

    extern bool FLAG_if_SPI_ConfigHasDone;
    //endregion

    bool SPI_Config();

    void ResetValue();

    bool Config();

    int READ(int addre);

    int WRITE(int addre, int val);

    int SPI_check();

    bool GetGRAVITYvalue(double PreGra);    //without GRAVITY Value give 0

    void DesiseToAndUpdateGRAVITY();

    int Get_RAW_Dat();

    bool _START_RT_Gyro();

    void _RESET_RT_Gyro();

    void _RT_Gyro();
}

#endif //MPU9250_MPU9250_HPP
