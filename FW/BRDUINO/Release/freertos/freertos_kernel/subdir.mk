################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/croutine.c \
../freertos/freertos_kernel/event_groups.c \
../freertos/freertos_kernel/list.c \
../freertos/freertos_kernel/queue.c \
../freertos/freertos_kernel/stream_buffer.c \
../freertos/freertos_kernel/tasks.c \
../freertos/freertos_kernel/timers.c 

OBJS += \
./freertos/freertos_kernel/croutine.o \
./freertos/freertos_kernel/event_groups.o \
./freertos/freertos_kernel/list.o \
./freertos/freertos_kernel/queue.o \
./freertos/freertos_kernel/stream_buffer.o \
./freertos/freertos_kernel/tasks.o \
./freertos/freertos_kernel/timers.o 

C_DEPS += \
./freertos/freertos_kernel/croutine.d \
./freertos/freertos_kernel/event_groups.d \
./freertos/freertos_kernel/list.d \
./freertos/freertos_kernel/queue.d \
./freertos/freertos_kernel/stream_buffer.d \
./freertos/freertos_kernel/tasks.d \
./freertos/freertos_kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/%.o: ../freertos/freertos_kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\board" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\drivers" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\device" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\CMSIS" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class\cdc" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\class" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\osa" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\component\lists" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\device\source\khci" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\usb\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\generated" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\streamports\Jlink_RTT\include" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\Tracealyzer\config" -I"D:\LW-D\Workspace\MCUxpressoV11_1\BRDUINO\source\usb" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


