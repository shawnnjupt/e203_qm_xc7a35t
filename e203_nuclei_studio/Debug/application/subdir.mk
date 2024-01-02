################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application/aes.c \
../application/main.c \
../application/tinyaes_c.c 

OBJS += \
./application/aes.o \
./application/main.o \
./application/tinyaes_c.o 

C_DEPS += \
./application/aes.d \
./application/main.d \
./application/tinyaes_c.d 


# Each subdirectory must supply rules for building sources it contributes
application/%.o: ../application/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-nuclei-elf-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -mno-save-restore -O0 -ffunction-sections -fdata-sections -fno-common  -g -DDOWNLOAD_MODE=DOWNLOAD_MODE_ILM -DSOC_HBIRDV2 -DBOARD_MCU200T -I"D:\code\fpga\gitee\e203_qm_xc7a35t\e203_nuclei_studio\application" -I"D:\code\fpga\gitee\e203_qm_xc7a35t\e203_nuclei_studio\hbird_sdk\NMSIS\Core\Include" -I"D:\code\fpga\gitee\e203_qm_xc7a35t\e203_nuclei_studio\hbird_sdk\SoC\hbirdv2\Common\Include" -I"D:\code\fpga\gitee\e203_qm_xc7a35t\e203_nuclei_studio\hbird_sdk\SoC\hbirdv2\Board\mcu200t\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


