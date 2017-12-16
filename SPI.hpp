//
// Created by root on 17/07/08.
//

#ifndef TEPIA_SPI_HPP
#define TEPIA_SPI_HPP

class SPI {
private:
	PORT_t *SPI_SPI_PORT;
	SPI_t *SPI_SPI_NAME;
	PORT_t *SPI_PORT_PORT;
	int SPI_PORT_PIN;
    register8_t CONF;

	int SPI_TIMEOUT_CHECK();

public:

	int SPI_READ(int addre);

	int SPI_WRITE(int addre, int val);

	bool SPI_CONFIG(SPI_t *SPI_SPI_N, PORT_t *SPI_SPI_P, PORT_t *SPI_PORT_P, int SPI_PORT_PI, register8_t CONFIG);

	void SPI_ALL_CLEAR();

	void SPI_CS_HIGH();

	void SPI_CS_LOW();
};

#endif //TEPIA_SPI_HPP
