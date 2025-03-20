################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/clap.c \
../Core/Src/distance.c \
../Core/Src/game.c \
../Core/Src/handle.c \
../Core/Src/hm10.c \
../Core/Src/lcd.c \
../Core/Src/main.c \
../Core/Src/max7219.c \
../Core/Src/maze.c \
../Core/Src/move.c \
../Core/Src/mpu.c \
../Core/Src/mpu6050.c \
../Core/Src/sd_card.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/temp.c \
../Core/Src/wav.c \
../Core/Src/xpt2046.c 

OBJS += \
./Core/Src/clap.o \
./Core/Src/distance.o \
./Core/Src/game.o \
./Core/Src/handle.o \
./Core/Src/hm10.o \
./Core/Src/lcd.o \
./Core/Src/main.o \
./Core/Src/max7219.o \
./Core/Src/maze.o \
./Core/Src/move.o \
./Core/Src/mpu.o \
./Core/Src/mpu6050.o \
./Core/Src/sd_card.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/temp.o \
./Core/Src/wav.o \
./Core/Src/xpt2046.o 

C_DEPS += \
./Core/Src/clap.d \
./Core/Src/distance.d \
./Core/Src/game.d \
./Core/Src/handle.d \
./Core/Src/hm10.d \
./Core/Src/lcd.d \
./Core/Src/main.d \
./Core/Src/max7219.d \
./Core/Src/maze.d \
./Core/Src/move.d \
./Core/Src/mpu.d \
./Core/Src/mpu6050.d \
./Core/Src/sd_card.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/temp.d \
./Core/Src/wav.d \
./Core/Src/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/FatFs/src/drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/clap.d ./Core/Src/clap.o ./Core/Src/clap.su ./Core/Src/distance.d ./Core/Src/distance.o ./Core/Src/distance.su ./Core/Src/game.d ./Core/Src/game.o ./Core/Src/game.su ./Core/Src/handle.d ./Core/Src/handle.o ./Core/Src/handle.su ./Core/Src/hm10.d ./Core/Src/hm10.o ./Core/Src/hm10.su ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/max7219.d ./Core/Src/max7219.o ./Core/Src/max7219.su ./Core/Src/maze.d ./Core/Src/maze.o ./Core/Src/maze.su ./Core/Src/move.d ./Core/Src/move.o ./Core/Src/move.su ./Core/Src/mpu.d ./Core/Src/mpu.o ./Core/Src/mpu.su ./Core/Src/mpu6050.d ./Core/Src/mpu6050.o ./Core/Src/mpu6050.su ./Core/Src/sd_card.d ./Core/Src/sd_card.o ./Core/Src/sd_card.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/temp.d ./Core/Src/temp.o ./Core/Src/temp.su ./Core/Src/wav.d ./Core/Src/wav.o ./Core/Src/wav.su ./Core/Src/xpt2046.d ./Core/Src/xpt2046.o ./Core/Src/xpt2046.su

.PHONY: clean-Core-2f-Src

