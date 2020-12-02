################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/portable/MemMang/heap_4.c 

OBJS += \
./freertos/freertos_kernel/portable/MemMang/heap_4.o 

C_DEPS += \
./freertos/freertos_kernel/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/portable/MemMang/%.o: ../freertos/freertos_kernel/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\board" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\drivers" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\device" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\CMSIS" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class\cdc" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\osa" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\lists" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source\khci" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\generated" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\streamports\Jlink_RTT\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\config" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\usb" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


