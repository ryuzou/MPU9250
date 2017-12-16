cmake_minimum_required(VERSION 3.6)
project(MPU9250)

SET(CMAKE_C_COMPILER /usr/bin/avr-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/avr-g++)

SET(DEVICE "atxmega128a1u")
SET(FREQ "32000000")

SET(CMAKE_C_FLAGS "-Os  -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wall -std=gnu99 -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wall -Wl,--gc-sections -std=c++11")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


set(SOURCE_FILES main.cpp
        SPI.cpp #SPI.hpp
        #defines.hpp
        MPU9250.cpp #MPU9250.hpp
        INTERRUPTS.cpp
        #usart_xmega.hpp
        )
add_executable(MPU9250 ${SOURCE_FILES})

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND /usr/bin/avr-objcopy -O ihex -R.eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND /usr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND sudo modprobe ftdi_sio )
#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND sudo rmmod ftdi_sio )

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avrdude -v -F -c avrisp2 -P usb -p x128a1u -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex:i  )
