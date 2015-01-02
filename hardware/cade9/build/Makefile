###############################################################################
# Makefile for the project CADE9
###############################################################################

## General Flags
PROJECT = CADE9
MCU = atmega32
TARGET = CADE9.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2               -DF_CPU=16000000UL -O3 -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"C:\Users\Rohit\Documents\Downloads\Compressed\cade9\cocoOS" -I"C:\Users\Rohit\Documents\Downloads\Compressed\cade9\cade9" -I"C:\Users\Rohit\Documents\Downloads\Compressed\cade9\port"

## Objects that must be built in order to link
OBJECTS = os_event.o os_kernel.o os_lists.o os_sem.o os_task.o clock.o uart.o main.o display.o

## Objects explicitly added by the user
LINKONLYOBJECTS =

## Build
all: $(TARGET) CADE9.hex CADE9.eep size

## Compile
os_event.o: ../cocoOS/os_event.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

os_kernel.o: ../cocoOS/os_kernel.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

os_lists.o: ../cocoOS/os_lists.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

os_sem.o: ../cocoOS/os_sem.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

os_task.o: ../cocoOS/os_task.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clock.o: ../port/clock.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../port/uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../cade9/main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

display.o: ../cade9/display.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) CADE9.elf dep/* CADE9.hex CADE9.eep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
