################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client.cpp \
../DeliveryController.cpp \
../Logger.cpp \
../Message.cpp \
../MessageFactory.cpp \
../Server.cpp 

OBJS += \
./Client.o \
./DeliveryController.o \
./Logger.o \
./Message.o \
./MessageFactory.o \
./Server.o 

CPP_DEPS += \
./Client.d \
./DeliveryController.d \
./Logger.d \
./Message.d \
./MessageFactory.d \
./Server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


