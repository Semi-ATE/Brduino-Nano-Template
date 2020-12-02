################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_crc.c \
../drivers/fsl_dac.c \
../drivers/fsl_dspi.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_ftm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_pit.c \
../drivers/fsl_rnga.c \
../drivers/fsl_rtc.c \
../drivers/fsl_sim.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c \
../drivers/fsl_vref.c \
../drivers/fsl_wdog.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_crc.o \
./drivers/fsl_dac.o \
./drivers/fsl_dspi.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_ftm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_pit.o \
./drivers/fsl_rnga.o \
./drivers/fsl_rtc.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o \
./drivers/fsl_vref.o \
./drivers/fsl_wdog.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_crc.d \
./drivers/fsl_dac.d \
./drivers/fsl_dspi.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_ftm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_pit.d \
./drivers/fsl_rnga.d \
./drivers/fsl_rtc.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d \
./drivers/fsl_vref.d \
./drivers/fsl_wdog.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\board" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\drivers" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\device" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\CMSIS" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class\cdc" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\osa" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\lists" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source\khci" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\generated" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\streamports\Jlink_RTT\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\config" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\usb" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


