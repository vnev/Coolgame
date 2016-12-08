################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/src/AnimatedSprite.cpp \
../source/src/Game.cpp \
../source/src/Graphics.cpp \
../source/src/Input.cpp \
../source/src/Level.cpp \
../source/src/Player.cpp \
../source/src/Sprite.cpp \
../source/src/main.cpp 

OBJS += \
./source/src/AnimatedSprite.o \
./source/src/Game.o \
./source/src/Graphics.o \
./source/src/Input.o \
./source/src/Level.o \
./source/src/Player.o \
./source/src/Sprite.o \
./source/src/main.o 

CPP_DEPS += \
./source/src/AnimatedSprite.d \
./source/src/Game.d \
./source/src/Graphics.d \
./source/src/Input.d \
./source/src/Level.d \
./source/src/Player.d \
./source/src/Sprite.d \
./source/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/src/%.o: ../source/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/chookchutney/Documents/workspace/cavestory/source/headers" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


