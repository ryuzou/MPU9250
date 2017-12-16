//
// Created by root on 17/11/23.
//

#ifndef MPU9250_MPU9250_HPP
#define MPU9250_MPU9250_HPP

#define DEFMDatUpdateSEC 1

namespace MPU9250{

    bool FLAG_if_SPI_ConfigHasDone = 0;

    bool FLAG_if_using_RTGyro;
    bool FLAG_if_using_RTAccel;
    bool FLAG_if_using_RTMagnDeg;

    double GRAVITY;     //In M/Sec^2

    int FLAG_GRAVITY_Update_timing;
    int VGRAVITY_Update_timing;

    double ARAW_Accel_dat[3];
    double GRAW_Accel_dat[3];
    double RAW_Gyro_dat[3];

    double RAW_Past_Accel_dat[20][3];   //little value is younger.
    double RAW_Past_Gyro_dat[20][3];   //little value is younger.

    double _RT_Gyro_DPS[3];
    long double _RT_Gyro_Deg[3];
    long double _RT_Gyro_Rad[3];

    int MDatUpdateSEC;

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
