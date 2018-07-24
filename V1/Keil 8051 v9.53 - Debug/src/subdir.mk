################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/algo_sensor_processing_main.c \
../src/func.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/algo_sensor_processing_main.OBJ \
./src/func.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/algo_sensor_processing.h C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/func.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.1/Device/shared/si8051Base/SILABS_STARTUP.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/algo_sensor_processing_main.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/InitDevice.h C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/algo_sensor_processing.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdbool.h

src/func.OBJ: C:/Users/Raph/Desktop/bck/simplicity\ backup/algo_sensor_processing/inc/algo_sensor_processing.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.2/Device/shared/si8051Base/stdbool.h


