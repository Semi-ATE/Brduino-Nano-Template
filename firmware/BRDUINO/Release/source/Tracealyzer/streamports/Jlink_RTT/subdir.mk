################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Tracealyzer/streamports/Jlink_RTT/SEGGER_RTT.c \
../source/Tracealyzer/streamports/Jlink_RTT/trcStreamingPort.c 

OBJS += \
./source/Tracealyzer/streamports/Jlink_RTT/SEGGER_RTT.o \
./source/Tracealyzer/streamports/Jlink_RTT/trcStreamingPort.o 

C_DEPS += \
./source/Tracealyzer/streamports/Jlink_RTT/SEGGER_RTT.d \
./source/Tracealyzer/streamports/Jlink_RTT/trcStreamingPort.d 


# Each subdirectory must supply rules for building sources it contributes
source/Tracealyzer/streamports/Jlink_RTT/%.o: ../source/Tracealyzer/streamports/Jlink_RTT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\board" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\drivers" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\device" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\CMSIS" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class\cdc" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\osa" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\lists" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source\khci" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\generated" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\streamports\Jlink_RTT\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\config" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\usb" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


