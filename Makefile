# Project Settings
TARGET      := $(notdir $(CURDIR))
SOURCES     := src
INCLUDES    := include

# Check for devkitPro
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

# Include WUT rules
include $(DEVKITPRO)/wut/share/wut.mk

# Compiler Flags
# WUPS requires specific defines for plugin information
CFLAGS      += -O2 -Wall -fms-extensions
CXXFLAGS    += $(CFLAGS)

# Libraries: lwups is required for Aroma plugins
LIBS        := -lwups -lwut

# Build Rules
.PHONY: all clean

all: $(TARGET).wps

# Aroma plugins are essentially RPX files renamed to WPS
$(TARGET).wps: $(TARGET).rpx
	@echo "Converting RPX to WPS..."
	@cp $(TARGET).rpx $(TARGET).wps

$(TARGET).rpx: $(SOURCES)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCES)/*.c -o $@ $(LIBS)

clean:
	@echo "Cleaning project..."
	@rm -f *.wps *.rpx *.elf
