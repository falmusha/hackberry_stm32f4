## Makefile for STM32F4
# @author Thomas Reidemeister <treideme@uwaterloo.ca>
# @date 2013.01.27
TARGET=hackberry
EXECUTABLE=hackberry.elf

## Flags
LDFLAGS=-Wl,-T,stm32_flash.ld
CPU=cortex-m4
DEFS=-DUSE_STDPERIPH_DRIVER
OPTIMIZE=-O0 -g
MCFLAGS= -fno-common -mcpu=$(CPU) -mthumb -mthumb-interwork -Wall -mfloat-abi=softfp -mfpu=fpv4-sp-d16

## Configuration of paths
ROOT=Libraries

## Tool configuration
CC=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-gcc
LD=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-gcc
AR=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-ar
AS=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-as
CP=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-objcopy
OD=$(ROOT)/gcc-arm-none-eabi/bin/arm-none-eabi-objdump
BIN=$(CP) -O ihex 

## Individual libraries
CORE=$(ROOT)/CMSIS/Include
DEVICE=$(ROOT)/Device/STM32F4xx
PERIPH=$(ROOT)/STM32F4xx_StdPeriph_Driver

STM32_INCLUDES = -I./src \
	-I$(CORE) \
	-I$(DEVICE)/Include \
	-I$(PERIPH)/inc/ 

CFLAGS	= $(MCFLAGS) $(OPTIMIZE) $(DEFS) $(STM32_INCLUDES)
AFLAGS	= $(MCFLAGS) 

SRC = src/hackberry.c \
	  src/fifo_peripherals.c \
		src/camera_peripherals.c \
	  src/UART_Debug.c \
	  src/newlib_stubs.c \
	  src/system_stm32f4xx.c \
	  src/delay.c \
	  $(PERIPH)/src/stm32f4xx_rcc.c \
	  $(PERIPH)/src/stm32f4xx_exti.c \
	  $(PERIPH)/src/stm32f4xx_syscfg.c \
	  $(PERIPH)/src/stm32f4xx_gpio.c \
	  $(PERIPH)/src/stm32f4xx_tim.c \
	  $(PERIPH)/src/misc.c  
		#src/sccb.c \
		#src/ov7670.c \

STARTUP = startup_stm32f4xx.s

OBJDIR = .
OBJ = $(SRC:%.c=$(OBJDIR)/%.o) 

all: $(TARGET).hex
	@echo "*** Build Complete ***"
    
$(TARGET).hex: $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lm
	$(OD) -h -S $@ > $(TARGET).lst
    
program: $(TARGET).hex
	/usr/local/bin/openocd -f openocd.cfg
	@echo "*** STM32F4 Programming Complete ***"    

clean:
	rm -f $(TARGET)  $(TARGET).lst $(OBJ) $(AUTOGEN)  $(TARGET).out  $(TARGET).hex  $(TARGET).map \
	 $(TARGET).dmp  $(TARGET).elf
	@echo "*** Project Cleaned ***"
