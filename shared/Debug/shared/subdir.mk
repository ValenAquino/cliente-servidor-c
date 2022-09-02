################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../shared/shared.c 

C_DEPS += \
./shared/shared.d 

OBJS += \
./shared/shared.o 


# Each subdirectory must supply rules for building sources it contributes
shared/%.o: ../shared/%.c shared/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-shared

clean-shared:
	-$(RM) ./shared/shared.d ./shared/shared.o

.PHONY: clean-shared

