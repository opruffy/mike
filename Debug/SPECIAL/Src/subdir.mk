################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPECIAL/Src/buffer_lcd.c \
../SPECIAL/Src/buffer_usb.c \
../SPECIAL/Src/button.c \
../SPECIAL/Src/calc.c \
../SPECIAL/Src/clock.c \
../SPECIAL/Src/debug.c \
../SPECIAL/Src/measure.c \
../SPECIAL/Src/measure_period.c 

OBJS += \
./SPECIAL/Src/buffer_lcd.o \
./SPECIAL/Src/buffer_usb.o \
./SPECIAL/Src/button.o \
./SPECIAL/Src/calc.o \
./SPECIAL/Src/clock.o \
./SPECIAL/Src/debug.o \
./SPECIAL/Src/measure.o \
./SPECIAL/Src/measure_period.o 

C_DEPS += \
./SPECIAL/Src/buffer_lcd.d \
./SPECIAL/Src/buffer_usb.d \
./SPECIAL/Src/button.d \
./SPECIAL/Src/calc.d \
./SPECIAL/Src/clock.d \
./SPECIAL/Src/debug.d \
./SPECIAL/Src/measure.d \
./SPECIAL/Src/measure_period.d 


# Each subdirectory must supply rules for building sources it contributes
SPECIAL/Src/%.o: ../SPECIAL/Src/%.c SPECIAL/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/mega/study/bachlor/workspace/mike/LCD/Inc" -I"D:/mega/study/bachlor/workspace/mike/USB/Inc" -I"D:/mega/study/bachlor/workspace/mike/SPECIAL/Inc" -I"D:/mega/study/bachlor/workspace/mike/STM32/Inc" -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPECIAL-2f-Src

clean-SPECIAL-2f-Src:
	-$(RM) ./SPECIAL/Src/buffer_lcd.d ./SPECIAL/Src/buffer_lcd.o ./SPECIAL/Src/buffer_usb.d ./SPECIAL/Src/buffer_usb.o ./SPECIAL/Src/button.d ./SPECIAL/Src/button.o ./SPECIAL/Src/calc.d ./SPECIAL/Src/calc.o ./SPECIAL/Src/clock.d ./SPECIAL/Src/clock.o ./SPECIAL/Src/debug.d ./SPECIAL/Src/debug.o ./SPECIAL/Src/measure.d ./SPECIAL/Src/measure.o ./SPECIAL/Src/measure_period.d ./SPECIAL/Src/measure_period.o

.PHONY: clean-SPECIAL-2f-Src

