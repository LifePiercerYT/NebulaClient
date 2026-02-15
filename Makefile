.RECIPEPREFIX = >

TARGET      := NebulaClient

# Find all .cpp files in root or any subfolder (like src/)
CPPS        := $(shell find . -name "*.cpp")
# Include both root and the include folder for headers
INCLUDES    := -I. -Iinclude

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

include $(DEVKITPRO)/wut/share/wut.mk

CFLAGS      += -O2 -Wall -fms-extensions
CXXFLAGS    += $(CFLAGS)
LIBS        := -lwups -lwut

.PHONY: all clean

all: $(TARGET).wps

$(TARGET).wps: $(TARGET).rpx
>@echo "Creating Aroma Plugin: $@"
>@cp $(TARGET).rpx $(TARGET).wps

$(TARGET).rpx:
>@$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) $(CPPS) -o $@ $(LIBS)

clean:
>@echo "Cleaning project..."
>@rm -f *.wps *.rpx *.elf
