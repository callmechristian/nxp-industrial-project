################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/fsl_component_generic_list.c 

C_DEPS += \
./component/lists/fsl_component_generic_list.d 

OBJS += \
./component/lists/fsl_component_generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_K22F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\source" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\utilities" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\drivers" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\device" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\component\uart" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\component\lists" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\CMSIS" -I"C:\Users\siman\OneDrive\Desktop\SA\NXP-CUP\nxp-industrial-project\frdmk22f_lscan_cam\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

