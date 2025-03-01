TARGET = client
SRCS := $(shell find src -type f -name '*.c')
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBS = -lpsppower

INCDIR =
CFLAGS = -O2 -ffast-math -Wno-parentheses -Wall -Dclient -flto=$(shell nproc)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = client

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
