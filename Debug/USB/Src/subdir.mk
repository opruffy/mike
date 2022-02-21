################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB/Src/usb.c \
../USB/Src/usb_data.c \
../USB/Src/usb_file.c 

OBJS += \
./USB/Src/usb.o \
./USB/Src/usb_data.o \
./USB/Src/usb_file.o 

C_DEPS += \
./USB/Src/usb.d \
./USB/Src/usb_data.d \
./USB/Src/usb_file.d 


# Each subdirectory must supply rules for building sources it contributes
USB/Src/%.o: ../USB/Src/%.c USB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/mega/study/bachlor/workspace/mike/LCD/Inc" -I"D:/mega/study/bachlor/workspace/mike/USB/Inc" -I"D:/mega/study/bachlor/workspace/mike/SPECIAL/Inc" -I"D:/mega/study/bachlor/workspace/mike/STM32/Inc" -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB-2f-Src

clean-USB-2f-Src:
	-$(RM) ./USB/Src/usb.d ./USB/Src/usb.o ./USB/Src/usb_data.d ./USB/Src/usb_data.o ./USB/Src/usb_file.d ./USB/Src/usb_file.o

.PHONY: clean-USB-2f-Src

