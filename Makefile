# Project Settings
TARGET      := NebulaClient
SOURCES     := .
INCLUDES    := include

# Check for devkitPro
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

# Include WUT rules for Wii U
include $(DEVKITPRO)/wut/share/wut.mk

# Compiler Flags
CFLAGS      += -O2 -Wall -fms-extensions
CXXFLAGS    += $(CFLAGS)
LIBS        := -lwups -lwut

.PHONY: all clean

all: $(TARGET).wps

# Aroma plugins are RPX files renamed to .wps
$(TARGET).wps: $(TARGET).rpx
	@echo "Creating Aroma Plugin: $@"
	@cp $(TARGET).rpx $(TARGET).wps

# Compile all .cpp files found in the root directory
$(TARGET).rpx:
	@$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(LDFLAGS) *.cpp -o $@ $(LIBS)

clean:
	@echo "Cleaning project..."
	@rm -f *.wps *.rpx *.elf
