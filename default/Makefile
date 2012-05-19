###############################################################################
# Makefile for the project atomclock
###############################################################################

## General Flags
PROJECT = atomclock
MCU = atmega2560
TARGET = atomclock.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                                                    -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=atomclock.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"F:\Avr\AtomTrace\Test\atomclock\..\..\atomthreads-avr\include" 

## Library Directories
LIBDIRS = -L"F:\Avr\AtomTrace\atomthreads-avr\lib" 

## Libraries
LIBS = -latomthreads-avr 

## Objects that must be built in order to link
OBJECTS = startup_os.o uart.o main_thread.o clock_disp.o graphics_thread.o st7565r.o clock_update.o button.o EventSender.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) atomclock.hex atomclock.eep atomclock.lss## Compile
startup_os.o: ../startup_os.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main_thread.o: ../main_thread.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clock_disp.o: ../clock_disp.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

graphics_thread.o: ../graphics_thread.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

st7565r.o: ../st7565r.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clock_update.o: ../clock_update.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

button.o: ../button.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

EventSender.o: ../EventSender.c
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

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) atomclock.elf dep/* atomclock.hex atomclock.eep atomclock.lss atomclock.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

