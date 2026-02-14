#---------------------------------------------------------------------------------
# Project Metadata
#---------------------------------------------------------------------------------
TARGET      := NebulaClient
NAME      := NebulaClient
AUTHOR      := LifePiercer
DESCRIPTION := LifePiercer
VERSION     := 1.0.0

#---------------------------------------------------------------------------------
# Path Setup (Assuming devkitPro is installed)
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=/opt/devkitpro")
endif

include $(DEVKITPRO)/wut/ahare/wut.mk

#---------------------------------------------------------------------------------
# Build Directories
#---------------------------------------------------------------------------------
BUILD    := build
SOURCES    := src
INCLUDES := include

#---------------------------------------------------------------------------------
# Libraries & Flags
#---------------------------------------------------------------------------------
LIBS    := -lwups -lwut -lvpad
CXXFLAGS := $(WUT_CXXFLAGS) -02 -Wall -fno-strict-aliasing
CFLAGS      := $(WUT_CFLAGS) -02 -Wall
LDFLAGS     := $(WUT_LDFLAGS)

#---------------------------------------------------------------------------------
# Build Rules
#---------------------------------------------------------------------------------
.PHONY: all clean

all: $(TARGET).wps

$(TARGET).wps: $(TARGET).rpx
  @echo "Packaging into WPS..."
  @$(DEVKITPRO)/tools/bin/wups-tool --create $@ --rpx $< --name "$(NAME)" --author "$(AUTHOR)" --description "$(VERSION)"

$(TARGET).rpx: $(SOURCES)/main.cpp
  @mkdir -p $(BUILD)
  powerpc-eabi-g++ $(CXXFLAGS) -I$(INCLUDES) $(SOURCES)/main.cpp $(LDFLAGS) $(LIBS) -o $@

clean:
  @rm -rf $(BUILD) $(TARGET).rpx $(TARGET).wps
  @echo "Cleaned up build files."
