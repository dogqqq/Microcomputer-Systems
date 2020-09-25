################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../copyBlock.s 

OBJS += \
./copyBlock.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.s
	@echo 'Building file: $<'
	@echo 'Invoking: Andes Assembler'
	$(CROSS_COMPILE)as -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


