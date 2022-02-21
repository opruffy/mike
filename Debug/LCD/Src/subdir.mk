################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD/Src/lcd.c \
../LCD/Src/lcd_body.c \
../LCD/Src/lcd_body_debug.c \
../LCD/Src/lcd_body_graph.c \
../LCD/Src/lcd_body_settings.c \
../LCD/Src/lcd_body_value.c \
../LCD/Src/lcd_display_view.c \
../LCD/Src/lcd_driver.c \
../LCD/Src/lcd_function.c \
../LCD/Src/lcd_head.c \
../LCD/Src/lcd_matrix.c \
../LCD/Src/lcd_menu.c \
../LCD/Src/lcd_symbol.c \
../LCD/Src/lcd_time.c 

OBJS += \
./LCD/Src/lcd.o \
./LCD/Src/lcd_body.o \
./LCD/Src/lcd_body_debug.o \
./LCD/Src/lcd_body_graph.o \
./LCD/Src/lcd_body_settings.o \
./LCD/Src/lcd_body_value.o \
./LCD/Src/lcd_display_view.o \
./LCD/Src/lcd_driver.o \
./LCD/Src/lcd_function.o \
./LCD/Src/lcd_head.o \
./LCD/Src/lcd_matrix.o \
./LCD/Src/lcd_menu.o \
./LCD/Src/lcd_symbol.o \
./LCD/Src/lcd_time.o 

C_DEPS += \
./LCD/Src/lcd.d \
./LCD/Src/lcd_body.d \
./LCD/Src/lcd_body_debug.d \
./LCD/Src/lcd_body_graph.d \
./LCD/Src/lcd_body_settings.d \
./LCD/Src/lcd_body_value.d \
./LCD/Src/lcd_display_view.d \
./LCD/Src/lcd_driver.d \
./LCD/Src/lcd_function.d \
./LCD/Src/lcd_head.d \
./LCD/Src/lcd_matrix.d \
./LCD/Src/lcd_menu.d \
./LCD/Src/lcd_symbol.d \
./LCD/Src/lcd_time.d 


# Each subdirectory must supply rules for building sources it contributes
LCD/Src/%.o: ../LCD/Src/%.c LCD/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/mega/study/bachlor/workspace/mike/LCD/Inc" -I"D:/mega/study/bachlor/workspace/mike/USB/Inc" -I"D:/mega/study/bachlor/workspace/mike/SPECIAL/Inc" -I"D:/mega/study/bachlor/workspace/mike/STM32/Inc" -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LCD-2f-Src

clean-LCD-2f-Src:
	-$(RM) ./LCD/Src/lcd.d ./LCD/Src/lcd.o ./LCD/Src/lcd_body.d ./LCD/Src/lcd_body.o ./LCD/Src/lcd_body_debug.d ./LCD/Src/lcd_body_debug.o ./LCD/Src/lcd_body_graph.d ./LCD/Src/lcd_body_graph.o ./LCD/Src/lcd_body_settings.d ./LCD/Src/lcd_body_settings.o ./LCD/Src/lcd_body_value.d ./LCD/Src/lcd_body_value.o ./LCD/Src/lcd_display_view.d ./LCD/Src/lcd_display_view.o ./LCD/Src/lcd_driver.d ./LCD/Src/lcd_driver.o ./LCD/Src/lcd_function.d ./LCD/Src/lcd_function.o ./LCD/Src/lcd_head.d ./LCD/Src/lcd_head.o ./LCD/Src/lcd_matrix.d ./LCD/Src/lcd_matrix.o ./LCD/Src/lcd_menu.d ./LCD/Src/lcd_menu.o ./LCD/Src/lcd_symbol.d ./LCD/Src/lcd_symbol.o ./LCD/Src/lcd_time.d ./LCD/Src/lcd_time.o

.PHONY: clean-LCD-2f-Src

