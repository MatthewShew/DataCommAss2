OS = $(shell uname -s)

VERSION = DEBUG
PRODUCT = ReaderWare
PREFIX = 

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
AR = $(PREFIX)ar
RANLIB = $(PREFIX)ranlib


##############################################

# Common Directories
VPATH  = ..
VPATH  += ../Reader
VPATH  += ../Device
VPATH  += ../Protocol
VPATH  += ../Tag
VPATH  += ../Demo

INCLUDE  = -I..

ifeq "$(VERSION)" "RELEASE"

# -fPIC option required for compilation of SWIG bindings
  CFLAGS = -O2
  #CFLAGS = -O2 -fPIC
  LDFLAGS = 

else
ifeq "$(VERSION)" "DEBUG"

# -fPIC option required for compilation of SWIG bindings
  CFLAGS = -g -O0 -Wall -DDEBUG
  #CFLAGS = -g -O0 -Wall -DDEBUG -fPIC

endif
endif

##############################################

# Definitions

EXE = libstapi
OUTPUT_DIR = build
OBJS += SkyeTekAPI.o \
	asn1.o utils.o CRC.o STPv2.o STPv3.o \
	TagFactory.o \
	Tag.o GenericTag.o DesfireTag.o Iso14443ATag.o Iso14443BTag.o \
	ReaderFactory.o \
	SkyeTekReader.o SkyeTekReaderFactory.o \
	DeviceFactory.o \
	SerialDeviceFactory.o  SerialDevice.o \
	Demo.o

##############################################

ifeq ($(OS),Linux)
  VPATH  += ../Device/USB
  CFLAGS += -DLINUX -DHAVE_PTHREAD -DHAVE_LIBUSB
  OBJS += USBDeviceFactory.o USBDevice.o
endif

all: build_msg $(EXE).a
	@echo; echo $(VERSION) build complete; echo

$(EXE).a: $(OBJS)
	$(AR) ru $@ $(OBJS)
	@echo

%.a: %.o
	$(RANLIB) $@
	@echo

%.o: %.c
	$(CC) -c $(INCLUDE) $(CFLAGS) $<
	@echo

clean:
	rm -f *.o *.elf *.lst *.s *.i *.a

build_msg:
	@echo; echo $(VERSION); echo

