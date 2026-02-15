# Project Settings
TARGET      := $(notdir $(CURDIR))
SOURCES     := .
INCLUDES    := include

# Check for devkitPro
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

# Include WUT rules for Wii U
include $(DEVKITPRO)/wut/share/wut.mk

# Compiler Flags for C++
CXXFLAGS    += -O2 -Wall -fms-extensions
# Required for Aroma plugins
LIBS        := -lwups -lwut

.PHONY: all clean

all: $(TARGET).wps

# Aroma plugins are RPX files renamed to WPS
$(TARGET).wps: $(TARGET).rpx
	@echo "Creating Aroma plugin: $@"
	@cp $(TARGET).rpx $(TARGET).wps

# Compile all .cpp files in the root folder
$(TARGET).rpx:
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) *.cpp -o $@ $(LIBS)

clean:
	@echo "Cleaning project..."
	@rm -f *.wps *.rpx *.elf
