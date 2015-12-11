################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../Color.cpp \
../Group.cpp \
../Hit.cpp \
../ImagePlane.cpp \
../Light.cpp \
../Ray.cpp \
../Render.cpp \
../Scene.cpp \
../Sphere.cpp \
../Transform.cpp \
../Triangle.cpp \
../Vector.cpp \
../surface.cpp 

O_SRCS += \
../Camera.o \
../Color.o \
../Hit.o \
../ImagePlane.o \
../Light.o \
../Ray.o \
../Scene.o \
../Sphere.o \
../Triangle.o \
../Vector.o 

OBJS += \
./Camera.o \
./Color.o \
./Group.o \
./Hit.o \
./ImagePlane.o \
./Light.o \
./Ray.o \
./Render.o \
./Scene.o \
./Sphere.o \
./Transform.o \
./Triangle.o \
./Vector.o \
./surface.o 

CPP_DEPS += \
./Camera.d \
./Color.d \
./Group.d \
./Hit.d \
./ImagePlane.d \
./Light.d \
./Ray.d \
./Render.d \
./Scene.d \
./Sphere.d \
./Transform.d \
./Triangle.d \
./Vector.d \
./surface.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -framework OpenGL -framework GLUT -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


